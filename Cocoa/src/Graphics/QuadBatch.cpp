#include "Graphics/QuadBatch.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/SpriteManager.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Graphics/RenderStatistics.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/Sprite.hpp"

#include <algorithm>

namespace Cocoa::Graphics
{
    QuadBatch::QuadBatch(
        GraphicsDevice& graphicsDevice,
        ShaderManager& shaderManager,
        TextureManager& textureManager,
        MaterialManager& materialManager,
        SpriteManager& spriteManager,
        RenderStatistics& renderStatistics)
    :
        m_graphicsDevice(graphicsDevice),
        m_shaderManager(shaderManager),
        m_textureManager(textureManager),
        m_materialManager(materialManager),
        m_spriteManager(spriteManager),
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
            { 3, ShaderDataType::UInt, "a_TexIndex" },
        };

        m_vao = m_graphicsDevice.CreateVertexArray();
        m_vbo = m_graphicsDevice.CreateVertexBuffer(maxVertices * sizeof(QuadVertex), layout);
        m_ibo = m_graphicsDevice.CreateIndexBuffer(quadIndices, static_cast<uint32_t>(maxIndices));
        m_vao->AddVertexBuffer(*m_vbo);
        m_vao->SetIndexBuffer(*m_ibo);

        delete[] quadIndices;
    }

    QuadBatch::~QuadBatch() = default;

    void QuadBatch::Draw(
        const Math::Matrix4f& modelMatrix,
        const MaterialHandle materialHandle,
        const TextureHandle textureHandle)
    {
        const Material& material = m_materialManager.Get(materialHandle);
        const Math::Vector4f color{ material.Tint.R, material.Tint.G, material.Tint.B, material.Tint.A };
        const std::array<QuadVertex, 4> vertices = BuildVertices(
            modelMatrix,
            color,
            {0.0f, 0.0f},
            {1.0f, 1.0f}
        );

        m_drawCommands.emplace_back(
            material.Shader,
            textureHandle,
            vertices
        );
    }

    void QuadBatch::Draw(
        const Math::Matrix4f& modelMatrix,
        const MaterialHandle materialHandle,
        const SpriteHandle spriteHandle)
    {
        const Material& material = m_materialManager.Get(materialHandle);
        const Sprite& sprite = m_spriteManager.Get(spriteHandle);
        const Math::Vector4f color{ material.Tint.R, material.Tint.G, material.Tint.B, material.Tint.A };
        const std::array<QuadVertex, 4> vertices = BuildVertices(modelMatrix, color, sprite.MinUV, sprite.MaxUV);

        m_drawCommands.emplace_back(
            material.Shader,
            sprite.Texture,
            vertices
        );
    }

    void QuadBatch::Flush(const Math::Matrix4f& viewProjectionMatrix)
    {
        if (m_drawCommands.empty())
            return;

        BuildBatch(viewProjectionMatrix);

        m_drawCommands.clear();
        m_renderStatistics.BatchFlushCount++;
    }

    void QuadBatch::BuildBatch(const Math::Matrix4f& viewProjectionMatrix)
    {
        uint32_t batchCounter{ 0 };
        BatchData batchData{.Shader =  m_drawCommands[0].Shader};

        for (QuadDrawCommand& command : m_drawCommands)
        {
            auto texSlotActiveEnd = batchData.Textures.Data.begin() + batchData.Textures.Count;
            auto texSlotIterator = std::find_if(
                batchData.Textures.Data.begin(),
                texSlotActiveEnd,
                [&](const TextureHandle& textureHandle)
                {
                    return textureHandle.Id == command.Texture.Id;
                }
            );

            if (command.Shader.Id != batchData.Shader.Id ||
                (texSlotIterator == texSlotActiveEnd && batchData.Textures.Count == TextureSlots::MaxCount) ||
                batchCounter == m_maxQuadCount)
            {
                ExecuteBatch(batchData, viewProjectionMatrix);
                batchCounter = 0;
                batchData.Textures.Count = 0;
                batchData.Vertices.clear();
                texSlotActiveEnd = batchData.Textures.Data.begin();
                texSlotIterator = texSlotActiveEnd;
                batchData.Shader = command.Shader;
            }

            uint32_t currentTexSlotIndex;
            if (texSlotIterator == texSlotActiveEnd)
            {
                currentTexSlotIndex = batchData.Textures.Count;
                batchData.Textures.Data[batchData.Textures.Count] = command.Texture;
                batchData.Textures.Count++;
            }
            else
            {
                currentTexSlotIndex = static_cast<uint32_t>(
                    texSlotIterator - batchData.Textures.Data.begin()
                );
            }

            for (auto& quadVertex : command.Vertices)
            {
                quadVertex.TexIndex = currentTexSlotIndex;
            }

            batchData.Vertices.insert(batchData.Vertices.end(),
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

    void QuadBatch::ExecuteBatch(
        const BatchData& batchData,
        const Math::Matrix4f& viewProjectionMatrix) const
    {
        const Shader& shader = m_shaderManager.Get(batchData.Shader);
        const std::array samplerUnits = CreateSamplerUnits();

        m_vbo->SetData(
            batchData.Vertices.data(),
            static_cast<uint32_t>(batchData.Vertices.size() * sizeof(QuadVertex))
        );
        shader.Bind();
        shader.SetMatrix4("u_ViewProjection", viewProjectionMatrix);
        shader.SetIntArray("u_Textures", samplerUnits.data(), samplerUnits.size());
        for (uint32_t i = 0; i < batchData.Textures.Count; ++i)
        {
            const Texture2D& texture = m_textureManager.Get(batchData.Textures.Data[i]);
            texture.Bind(i);
        }
        const auto quadCount = static_cast<uint32_t>(batchData.Vertices.size() / 4);
        const uint32_t indexCount = quadCount * 6;
        m_graphicsDevice.DrawIndexed(*m_vao, indexCount);
        shader.Unbind();

        m_renderStatistics.VertexCount += quadCount * 4;
        m_renderStatistics.IndexCount += indexCount;
        m_renderStatistics.DrawCount++;
    }

    std::array<int, QuadBatch::TextureSlots::MaxCount> QuadBatch::CreateSamplerUnits()
    {
        std::array<int, TextureSlots::MaxCount> units{};
        for (uint32_t i = 0; i < TextureSlots::MaxCount; ++i)
        {
            units[i] = static_cast<int>(i);
        }

        return units;
    }

    std::array<QuadBatch::QuadVertex, 4> QuadBatch::BuildVertices(
        const Math::Matrix4f& modelMatrix,
        const Math::Vector4f& color,
        const Math::Vector2f& minUV,
        const Math::Vector2f& maxUV)
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

        return{
            // Bottom-Left
            QuadVertex{{ worldBottomLeft.X, worldBottomLeft.Y, worldBottomLeft.Z}, { minUV.X, minUV.Y }, color },
            // Bottom-Right
            QuadVertex{{ worldBottomRight.X, worldBottomRight.Y, worldBottomRight.Z }, { maxUV.X, minUV.Y }, color },
            // Top-Right
            QuadVertex{{worldTopRight.X, worldTopRight.Y, worldTopRight.Z}, {maxUV.X, maxUV.Y}, color },
            // Top-Left
            QuadVertex{{worldTopLeft.X, worldTopLeft.Y, worldTopLeft.Z}, { minUV.X, maxUV.Y}, color }
        };
    }
}
