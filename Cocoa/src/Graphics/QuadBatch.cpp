#include "Graphics/QuadBatch.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Graphics/RenderStatistics.hpp"
#include "Graphics/Material.hpp"

#include <algorithm>

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

    void QuadBatch::Draw(const Math::Matrix4f& modelMatrix, MaterialHandle materialHandle)
    {
        const Material& material = m_materialManager.Get(materialHandle);

        // Transform the quad's local-space corners into world space.
        const Math::Vector4f worldBottomLeft =
            modelMatrix * Math::Vector4f{-0.5f, -0.5f, 0.0f, 1.0f };

        const Math::Vector4f worldBottomRight =
            modelMatrix * Math::Vector4f{ 0.5f, -0.5f, 0.0f, 1.0f };

        const Math::Vector4f worldTopRight =
            modelMatrix * Math::Vector4f{ 0.5f, 0.5f, 0.0f, 1.0f };

        const Math::Vector4f worldTopLeft =
            modelMatrix * Math::Vector4f{ -0.5f, 0.5f, 0.0f, 1.0f };

        const Math::Vector4f color{ material.Tint.R, material.Tint.G, material.Tint.B, material.Tint.A };

        const std::array<QuadVertex, 4> vertices =
        {
            // Bottom-Left
            QuadVertex{{ worldBottomLeft.X, worldBottomLeft.Y, worldBottomLeft.Z}, { 0.0f, 0.0f }, color },
            // Bottom-Right
            QuadVertex{{ worldBottomRight.X, worldBottomRight.Y, worldBottomRight.Z }, { 1.0f, 0.0f }, color },
            // Top-Right
            QuadVertex{{worldTopRight.X, worldTopRight.Y, worldTopRight.Z}, {1.0f, 1.0f}, color },
            // Top-Left
            QuadVertex{{worldTopLeft.X, worldTopLeft.Y, worldTopLeft.Z}, { 0.0f, 1.0f}, color }
        };

        m_drawCommands.emplace_back(
            QuadDrawCommand
            {
                .MaterialRef = material,
                .Vertices = vertices
            }
        );
    }

    void QuadBatch::Flush(const Math::Matrix4f& viewProjectionMatrix)
    {
        if (m_drawCommands.empty())
            return;

        uint32_t batchCounter{ 0 };
        TextureSlots textureSlots;
        std::vector<QuadVertex> batchVertices;
        Material currentMaterial = m_drawCommands[0].MaterialRef;

        for (QuadDrawCommand& command : m_drawCommands)
        {
            auto texSlotActiveEnd = textureSlots.Data.begin() + textureSlots.Count;
            auto texSlotIterator = std::find_if(
                textureSlots.Data.begin(),
                texSlotActiveEnd,
                [&](const uint32_t& texId)
                {
                    return texId == command.MaterialRef.Texture.Id;
                }
            );

            if (command.MaterialRef.Shader.Id != currentMaterial.Shader.Id ||
                (texSlotIterator == texSlotActiveEnd && textureSlots.Count == TextureSlots::MaxCount) ||
                batchCounter == m_maxQuadCount)
            {
                FlushBatch(
                    currentMaterial,
                    viewProjectionMatrix,
                    batchVertices,
                    textureSlots
                );
                batchCounter = 0;
                textureSlots.Count = 0;
                batchVertices.clear();
                texSlotActiveEnd = textureSlots.Data.begin();
                texSlotIterator = texSlotActiveEnd;
                currentMaterial = command.MaterialRef;
            }

            uint32_t currentTexSlotIndex;
            if (texSlotIterator == texSlotActiveEnd)
            {
                currentTexSlotIndex = textureSlots.Count;
                textureSlots.Data[textureSlots.Count] = command.MaterialRef.Texture.Id;
                textureSlots.Count++;
            }
            else
            {
                currentTexSlotIndex = static_cast<uint32_t>(
                    texSlotIterator - textureSlots.Data.begin()
                );
            }

            for (auto& quadVertex : command.Vertices)
            {
                quadVertex.TexIndex = currentTexSlotIndex;
            }

            batchVertices.insert(batchVertices.end(),
                                 command.Vertices.begin(),
                                 command.Vertices.end()
            );
            batchCounter++;
        }

        if (!batchVertices.empty())
        {
            FlushBatch(
                currentMaterial,
                viewProjectionMatrix,
                batchVertices,
                textureSlots
            );
            batchVertices.clear();
        }

        m_drawCommands.clear();
        m_renderStatistics.BatchFlushCount++;
    }

    void QuadBatch::FlushBatch(
        const Material& material,
        const Math::Matrix4f& viewProjectionMatrix,
        const std::vector<QuadVertex>& batchVertices,
        const TextureSlots& textureSlots) const
    {
        const Shader& shader = m_shaderManager.Get(material.Shader);
        const std::array samplerUnits = CreateSamplerUnits();

        m_vbo->SetData(
            batchVertices.data(),
            static_cast<uint32_t>(batchVertices.size() * sizeof(QuadVertex))
        );
        shader.Bind();
        shader.SetMatrix4("u_ViewProjection", viewProjectionMatrix);
        shader.SetIntArray("u_Textures", samplerUnits.data(), samplerUnits.size());
        for (uint32_t i = 0; i < textureSlots.Count; ++i)
        {
            const Texture2D& texture = m_textureManager.Get({textureSlots.Data[i]});
            texture.Bind(i);
        }
        const auto quadCount = static_cast<uint32_t>(batchVertices.size() / 4);
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
}
