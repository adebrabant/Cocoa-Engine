#include "Graphics/QuadBatch.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/RenderStatistics.hpp"

namespace Cocoa::Graphics
{
    QuadBatch::QuadBatch(
        GraphicsDevice& graphicsDevice,
        ShaderManager& shaderManager,
        TextureManager& textureManager,
        MaterialManager& materialManager,
        RenderStatistics& renderStatistics)
    :
        m_graphicsDevice(graphicsDevice),
        m_shaderManager(shaderManager),
        m_textureManager(textureManager),
        m_materialManager(materialManager),
        m_renderStatistics(renderStatistics),
        m_maxQuadCount(20000)
    {
        const uint32_t maxVertices{ m_maxQuadCount * 4 };
        const uint32_t maxIndices{ m_maxQuadCount * 6 };
        const auto quadIndices = new uint32_t[maxIndices];
        uint32_t offset{ 0 };
        for (uint32_t i = 0; i < maxIndices; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        const BufferLayout layout =
        {
            { 0, ShaderDataType::Float3, "a_Position" },
            { 1, ShaderDataType::Float2, "a_TexCoord" },
            { 2, ShaderDataType::Float4, "a_Color" },
        };

        m_vao = m_graphicsDevice.CreateVertexArray();
        m_vbo = m_graphicsDevice.CreateVertexBuffer(maxVertices * sizeof(QuadVertex), layout);
        m_ibo = m_graphicsDevice.CreateIndexBuffer(quadIndices, static_cast<uint32_t>(maxIndices));
        m_vao->AddVertexBuffer(*m_vbo);
        m_vao->SetIndexBuffer(*m_ibo);

        delete[] quadIndices;
    }

    QuadBatch::~QuadBatch() = default;

    void QuadBatch::Draw(const Math::Matrix4f& modelMatrix, MaterialHandle materialHandle)
    {
        // Transform the quad's local-space corners into world space.
        const Math::Vector4f worldBottomLeft =
            modelMatrix * Math::Vector4f{-0.5f, -0.5f, 0.0f, 1.0f };

        const Math::Vector4f worldBottomRight =
            modelMatrix * Math::Vector4f{ 0.5f, -0.5f, 0.0f, 1.0f };

        const Math::Vector4f worldTopRight =
            modelMatrix * Math::Vector4f{ 0.5f, 0.5f, 0.0f, 1.0f };

        const Math::Vector4f worldTopLeft =
            modelMatrix * Math::Vector4f{ -0.5f, 0.5f, 0.0f, 1.0f };

        constexpr Math::Vector4f defaultWhiteColor{ 1.0f, 1.0f, 1.0f, 1.0f };

        const std::array<QuadVertex, 4> vertices =
        {
            // Bottom-Left
            QuadVertex{{ worldBottomLeft.X, worldBottomLeft.Y, worldBottomLeft.Z}, { 0.0f, 0.0f }, defaultWhiteColor},
            // Bottom-Right
            QuadVertex{{ worldBottomRight.X, worldBottomRight.Y, worldBottomRight.Z }, { 1.0f, 0.0f }, defaultWhiteColor},
            // Top-Right
            QuadVertex{{worldTopRight.X, worldTopRight.Y, worldTopRight.Z}, {1.0f, 1.0f}, defaultWhiteColor},
            // Top-Left
            QuadVertex{{worldTopLeft.X, worldTopLeft.Y, worldTopLeft.Z}, { 0.0f, 1.0f}, defaultWhiteColor}
        };

        m_drawCommands.emplace_back(QuadDrawCommand{ .Material = materialHandle, .Vertices = vertices});
    }

    void QuadBatch::Flush(const Math::Matrix4f& viewProjectionMatrix)
    {
        if (m_drawCommands.empty())
            return;

        uint32_t batchCounter{ 0 };
        std::vector<QuadVertex> batchVertices;
        Material currentMaterial = m_materialManager.Get(m_drawCommands[0].Material);
        for (const QuadDrawCommand& command : m_drawCommands)
        {
            const Material& commandMaterial = m_materialManager.Get(command.Material);
            if (commandMaterial.Id != currentMaterial.Id &&
                commandMaterial.ShaderId.Id != currentMaterial.ShaderId.Id &&
                commandMaterial.TextureId.Id != currentMaterial.TextureId.Id &&
                commandMaterial.Tint != currentMaterial.Tint ||
                batchCounter == m_maxQuadCount)
            {
                FlushBatch(currentMaterial, viewProjectionMatrix, batchVertices);
                batchVertices.clear();
                currentMaterial = commandMaterial;
                batchCounter = 0;
            }

            batchVertices.insert(batchVertices.end(),
                                 command.Vertices.begin(),
                                 command.Vertices.end()
            );
            batchCounter++;
        }

        if (!batchVertices.empty())
        {
            FlushBatch(currentMaterial, viewProjectionMatrix, batchVertices);
            batchVertices.clear();
        }

        m_drawCommands.clear();
        m_renderStatistics.BatchFlushCount++;
    }

    void QuadBatch::FlushBatch(
        const Material& material,
        const Math::Matrix4f& viewProjectionMatrix,
        const std::vector<QuadVertex>& batchVertices) const
    {
        const Shader& shader = m_shaderManager.Get(material.ShaderId);
        const Texture2D& texture = m_textureManager.Get(material.TextureId);
        m_vbo->SetData(
            batchVertices.data(),
            static_cast<uint32_t>(batchVertices.size() * sizeof(QuadVertex))
        );

        shader.Bind();
        texture.Bind(0);
        shader.SetInt("u_Texture", 0);
        shader.SetVector4(
            "u_Tint",
            {
                material.Tint.R,
                material.Tint.G,
                material.Tint.B,
                material.Tint.A
            }
        );
        shader.SetMatrix4("u_ViewProjection", viewProjectionMatrix);
        const auto quadCount = static_cast<uint32_t>(batchVertices.size() / 4);
        const uint32_t indexCount = quadCount * 6;
        m_graphicsDevice.DrawIndexed(*m_vao, indexCount);
        shader.Unbind();

        m_renderStatistics.VertexCount += quadCount * 4;
        m_renderStatistics.IndexCount += indexCount;
        m_renderStatistics.DrawCount++;
    }
}
