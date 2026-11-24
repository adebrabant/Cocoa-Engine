#include "Graphics/LineBatch.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/RenderStatistics.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/RenderStatistics.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Graphics/Shader.hpp"

namespace Cocoa::Graphics
{
    LineBatch::LineBatch(
        GraphicsDevice& graphicsDevice,
        MaterialManager& materialManager,
        ShaderManager& shaderManager,
        RenderStatistics& renderStats)
    :
        m_graphicsDevice(graphicsDevice),
        m_materialManager(materialManager),
        m_shaderManager(shaderManager),
        m_renderStats(renderStats),
        m_maxLineCount(20000)
    {
        const uint32_t maxVertices{ m_maxLineCount * 4 };
        const uint32_t maxIndices{ m_maxLineCount * 6 };
        const auto lineIndices = new uint32_t[maxIndices];
        uint32_t offset{ 0 };
        for (uint32_t i = 0; i < maxIndices; i += 6)
        {
            lineIndices[i + 0] = offset + 0;
            lineIndices[i + 1] = offset + 1;
            lineIndices[i + 2] = offset + 2;

            lineIndices[i + 3] = offset + 2;
            lineIndices[i + 4] = offset + 3;
            lineIndices[i + 5] = offset + 0;

            offset += 4;
        }

        const BufferLayout layout =
        {
            { 0, ShaderDataType::Float3, "a_WorldPosition" },
            { 1, ShaderDataType::Float2, "a_LocalPosition" },
            { 2, ShaderDataType::Float4, "a_Color" },
            { 3, ShaderDataType::Float2, "a_Fade" }
        };

        m_vao = m_graphicsDevice.CreateVertexArray();
        m_vbo = m_graphicsDevice.CreateVertexBuffer(maxVertices * sizeof(LineVertex), layout);
        m_ibo = m_graphicsDevice.CreateIndexBuffer(lineIndices, maxVertices);
        m_vao->AddVertexBuffer(*m_vbo);
        m_vao->SetIndexBuffer(*m_ibo);

        delete[] lineIndices;
    }

    void LineBatch::Draw(
        const MaterialHandle materialHandle,
        const Math::Matrix4f& modelMatrix,
        const Math::Vector4f& color,
        const Math::Vector2f& startPoint,
        const Math::Vector2f& endPoint,
        const float thickness,
        const float fade)
    {
        const auto material = m_materialManager.Get(materialHandle);
        const auto direction = endPoint - startPoint;
        const auto normalizedDirection = direction.Normalized();
        const Math::Vector2f perpendicular(-normalizedDirection.Y, normalizedDirection.X);
        const auto offset = perpendicular * (thickness / 2);
        // Apply proportional scaling for x-axis
        const auto calculatedFade = Math::Vector2f(fade * (thickness/direction.Length()), fade);

        const auto v0 = startPoint + offset;
        const Math::Vector4f worldTopLeft =
            modelMatrix * Math::Vector4f{ v0.X, v0.Y, 0.0f, 1.0f };

        const auto v1 = startPoint - offset;
        const Math::Vector4f worldBottomLeft =
            modelMatrix * Math::Vector4f{ v1.X, v1.Y, 0.0f, 1.0f };

        const auto v2 = endPoint - offset;
        const Math::Vector4f worldBottomRight =
            modelMatrix * Math::Vector4f{ v2.X, v2.Y, 0.0f, 1.0f };

        const auto v3 = endPoint + offset;
        const Math::Vector4f worldTopRight =
            modelMatrix * Math::Vector4f{ v3.X, v3.Y, 0.0f, 1.0f };

        std::array<LineVertex, 4> vertices
        {
            // Bottom-Left
            LineVertex
            {
                .WorldPosition = { worldBottomLeft.X, worldBottomLeft.Y, worldBottomLeft.Z },
                .LocalPosition = { -0.5f, -0.5f },
                .Color = color,
                .Fade = calculatedFade
            },
            // Bottom-Right
            LineVertex
            {
                .WorldPosition = { worldBottomRight.X, worldBottomRight.Y, worldBottomRight.Z },
                .LocalPosition = { 0.5f, -0.5f },
                .Color = color,
                .Fade = calculatedFade
            },
            // Top-Right
            LineVertex
            {
                .WorldPosition = { worldTopRight.X, worldTopRight.Y, worldTopRight.Z },
                .LocalPosition = { 0.5f, 0.5f },
                .Color = color,
                .Fade = calculatedFade
            },
            // Top-Left
            LineVertex
            {
                .WorldPosition = { worldTopLeft.X, worldTopLeft.Y, worldTopLeft.Z },
                .LocalPosition = { -0.5f, 0.5f },
                .Color = color,
                .Fade = calculatedFade
            }
        };

        m_drawCommands.emplace_back(
            material.Shader,
            material.Blend,
            vertices
        );
    }

    void LineBatch::Flush(const Math::Matrix4f &viewProjectionMatrix)
    {
        if (m_drawCommands.empty())
            return;

        BuildBatch(viewProjectionMatrix);

        m_drawCommands.clear();
        m_renderStats.BatchFlushCount++;
    }

    void LineBatch::BuildBatch(const Math::Matrix4f& viewProjectionMatrix) const
    {
        uint32_t batchCounter{ 0 };
        LineBatchData batchData
        {
            .Shader = m_drawCommands[0].Shader,
            .Blend = m_drawCommands[0].Blend
        };

        for (const LineDrawCommand& command : m_drawCommands)
        {
            if (command.Shader.Id != batchData.Shader.Id ||
                command.Blend != batchData.Blend ||
                batchCounter == m_maxLineCount)
            {
                ExecuteBatch(batchData, viewProjectionMatrix);
                batchCounter = 0;
                batchData.Shader = command.Shader;
                batchData.Blend = command.Blend;
                batchData.Vertices.clear();
            }

            batchData.Vertices.insert(
                batchData.Vertices.end(),
                command.Vertices.begin(),
                command.Vertices.end()
            );

            batchCounter++;
        }

        if (!batchData.Vertices.empty())
        {
            ExecuteBatch(batchData, viewProjectionMatrix);
            batchData.Vertices.clear();
        }
    }

    void LineBatch::ExecuteBatch(
        const LineBatchData& batchData,
        const Math::Matrix4f& viewProjectionMatrix) const
    {
        const Shader& shader = m_shaderManager.Get(batchData.Shader);

        m_graphicsDevice.SetBlendMode(batchData.Blend);
        m_vbo->SetData(
            batchData.Vertices.data(),
            static_cast<uint32_t>(batchData.Vertices.size() * sizeof(LineVertex))
        );

        shader.Bind();
        shader.SetMatrix4("u_ViewProjectionMatrix", viewProjectionMatrix);

        const auto lineCount = static_cast<uint32_t>(batchData.Vertices.size() / 4);
        const uint32_t indexCount = lineCount * 6;

        m_graphicsDevice.DrawIndexed(*m_vao, indexCount);
        shader.Unbind();

        m_renderStats.VertexCount += lineCount * 4;
        m_renderStats.IndexCount += indexCount;
        m_renderStats.DrawCount++;
    }
}
