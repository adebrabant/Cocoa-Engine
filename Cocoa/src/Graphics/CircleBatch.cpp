#include "Graphics/CircleBatch.hpp"
#include "Graphics/CircleBatch.hpp"
#include "Graphics/CircleBatch.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/RenderStatistics.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Graphics/Shader.hpp"

namespace Cocoa::Graphics
{
    CircleBatch::CircleBatch(
        GraphicsDevice& graphicsDevice,
        MaterialManager& materialManager,
        ShaderManager& shaderManager,
        RenderStatistics& renderStats)
    :
        m_graphicsDevice(graphicsDevice),
        m_materialManager(materialManager),
        m_shaderManager(shaderManager),
        m_renderStatistics(renderStats),
        m_maxCircleCount(20000)
    {
        const uint32_t maxVertices{ m_maxCircleCount * 4 };
        const uint32_t maxIndices{ m_maxCircleCount * 6 };
        const auto circleIndices = new uint32_t[maxIndices];
        uint32_t offset{ 0 };
        for (uint32_t i = 0; i < maxIndices; i += 6)
        {
            circleIndices[i + 0] = offset + 0;
            circleIndices[i + 1] = offset + 1;
            circleIndices[i + 2] = offset + 2;

            circleIndices[i + 3] = offset + 2;
            circleIndices[i + 4] = offset + 3;
            circleIndices[i + 5] = offset + 0;

            offset += 4;
        }

        const BufferLayout layout =
        {
            {0, ShaderDataType::Float3, "a_WorldPosition"},
            {1, ShaderDataType::Float2, "a_LocalPosition"},
            {2, ShaderDataType::Float4, "a_Color"},
            {3, ShaderDataType::Float, "a_Thickness"},
            {4, ShaderDataType::Float, "a_Fade"},
        };

        m_vao = m_graphicsDevice.CreateVertexArray();
        m_vbo = m_graphicsDevice.CreateVertexBuffer(maxVertices * sizeof(CircleVertex), layout);
        m_ibo = m_graphicsDevice.CreateIndexBuffer(circleIndices, maxIndices);
        m_vao->AddVertexBuffer(*m_vbo);
        m_vao->SetIndexBuffer(*m_ibo);
        
        delete[] circleIndices;
    }

    CircleBatch::~CircleBatch() = default;

    void CircleBatch::Draw(
        const Math::Matrix4f& modelMatrix,
        const MaterialHandle materialHandle,
        const Math::Vector4f& color,
        const float thickness,
        const float fade)
    {
        const auto material = m_materialManager.Get(materialHandle);

        const Math::Vector4f worldBottomLeft =
            modelMatrix * Math::Vector4f{-0.5f, -0.5f, 0.0f, 1.0f };

        const Math::Vector4f worldBottomRight =
            modelMatrix * Math::Vector4f{ 0.5f, -0.5f, 0.0f, 1.0f };

        const Math::Vector4f worldTopRight =
            modelMatrix * Math::Vector4f{ 0.5f, 0.5f, 0.0f, 1.0f };

        const Math::Vector4f worldTopLeft =
            modelMatrix * Math::Vector4f{ -0.5f, 0.5f, 0.0f, 1.0f };

        std::array<CircleVertex, 4> vertices
        {
            // Bottom-Left
            CircleVertex
            {
                .Position = { worldBottomLeft.X, worldBottomLeft.Y, worldBottomLeft.Z },
                .Location = { -0.5f, -0.5f, },
                .Color = color,
                .Thickness = thickness,
                .Fade = fade
            },
            // Bottom-Right
            CircleVertex
            {
                .Position = { worldBottomRight.X, worldBottomRight.Y, worldBottomRight.Z },
                .Location = { 0.5f, -0.5f },
                .Color = color,
                .Thickness = thickness,
                .Fade = fade
            },
            // Top-Right
            CircleVertex
            {
                .Position = { worldTopRight.X, worldTopRight.Y, worldTopRight.Z },
                .Location = { 0.5f, 0.5f },
                .Color = color,
                .Thickness = thickness,
                .Fade = fade
            },
            // Top-Left
            CircleVertex
            {
                .Position = { worldTopLeft.X, worldTopLeft.Y, worldTopLeft.Z },
                .Location { -0.5f, 0.5f },
                .Color = color,
                .Thickness = thickness,
                .Fade = fade
            }
        };

        m_drawCommands.emplace_back(
            material.Shader,
            material.Blend,
            vertices
        );
    }

    void CircleBatch::Flush(const Math::Matrix4f& viewProjectionMatrix)
    {
        if (m_drawCommands.empty())
            return;

        BuildBatch(viewProjectionMatrix);

        m_drawCommands.clear();
        m_renderStatistics.BatchFlushCount++;
    }

    void CircleBatch::BuildBatch(const Math::Matrix4f& viewProjectionMatrix) const
    {
        uint32_t batchCounter{ 0 };
        CircleBatchData batchData
        {
            .Shader = m_drawCommands[0].Shader,
            .Blend = m_drawCommands[0].Blend
        };

        for (const CircleDrawCommand& command : m_drawCommands)
        {
            if (command.Shader.Id != batchData.Shader.Id ||
                command.Blend != batchData.Blend ||
                batchCounter == m_maxCircleCount)
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

    void CircleBatch::ExecuteBatch(
        const CircleBatchData& batchData,
        const Math::Matrix4f& viewProjectionMatrix) const
    {
        const Shader& shader = m_shaderManager.Get(batchData.Shader);

        m_graphicsDevice.SetBlendMode(batchData.Blend);
        m_vbo->SetData(
            batchData.Vertices.data(),
            static_cast<uint32_t>(batchData.Vertices.size() * sizeof(CircleVertex))
        );

        shader.Bind();
        shader.SetMatrix4("u_ViewProjection", viewProjectionMatrix);
        const auto circleCount = static_cast<uint32_t>(batchData.Vertices.size() / 4);
        const uint32_t indexCount = circleCount * 6;
        m_graphicsDevice.DrawIndexed(*m_vao, indexCount);
        shader.Unbind();

        m_renderStatistics.VertexCount += circleCount * 4;
        m_renderStatistics.IndexCount += indexCount;
        m_renderStatistics.DrawCount++;
    }
}
