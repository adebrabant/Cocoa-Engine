#include "graphics/QuadBatch.hpp"
#include "graphics/BufferLayout.hpp"
#include "graphics/GraphicsDevice.hpp"
#include "graphics/IndexBuffer.hpp"
#include "graphics/Material.hpp"
#include "graphics/MaterialManager.hpp"
#include "graphics/RenderStatistics.hpp"
#include "graphics/Shader.hpp"
#include "graphics/ShaderManager.hpp"
#include "graphics/Sprite.hpp"
#include "graphics/SpriteManager.hpp"
#include "graphics/Texture2D.hpp"
#include "graphics/TextureManager.hpp"
#include "graphics/VertexArray.hpp"
#include "graphics/VertexBuffer.hpp"

#include <algorithm>

namespace cocoa::graphics
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
            { 1, ShaderDataType::Float2, "a_LocalUV" },
            { 2, ShaderDataType::Float2, "a_MinUV" },
            { 3, ShaderDataType::Float2, "a_MaxUV" },
            { 4, ShaderDataType::Float2, "a_TilingFactor"},
            { 5, ShaderDataType::Float4, "a_Color" },
            { 6, ShaderDataType::UInt, "a_TexIndex" }
        };

        m_vao = m_graphicsDevice.createVertexArray();
        m_vbo = m_graphicsDevice.createVertexBuffer(maxVertices * sizeof(QuadVertex), layout);
        m_ibo = m_graphicsDevice.createIndexBuffer(quadIndices, maxIndices);
        m_vao->addVertexBuffer(*m_vbo);
        m_vao->setIndexBuffer(*m_ibo);

        delete[] quadIndices;
    }

    QuadBatch::~QuadBatch() = default;

    void QuadBatch::draw(
        const math::Matrix4f& modelMatrix,
        const MaterialHandle materialHandle,
        const TextureHandle textureHandle,
        const math::Vector2f& tilingFactor)
    {
        const Material& material = m_materialManager.get(materialHandle);
        const math::Vector4f color{ material.tint.r, material.tint.g, material.tint.b, material.tint.a };
        const std::array<QuadVertex, 4> vertices = buildVertices(
            modelMatrix,
            color,
            {0.0f, 0.0f},
            {1.0f, 1.0f},
            tilingFactor,
            false,
            false
        );

        m_drawCommands.emplace_back(
            material.shaderHandle,
            textureHandle,
            material.blendMode,
            vertices
        );
    }

    void QuadBatch::draw(
        const math::Matrix4f& modelMatrix,
        const MaterialHandle materialHandle,
        const SpriteHandle spriteHandle,
        const math::Vector2f& tilingFactor,
        const bool flipVertical,
        const bool flipHorizontal)
    {
        const Material& material = m_materialManager.get(materialHandle);
        const Sprite& sprite = m_spriteManager.get(spriteHandle);
        const math::Vector4f color{ material.tint.r, material.tint.g, material.tint.b, material.tint.a };
        const std::array<QuadVertex, 4> vertices = buildVertices(
            modelMatrix,
            color,
            sprite.minUV,
            sprite.maxUV,
            tilingFactor,
            flipVertical,
            flipHorizontal
        );

        m_drawCommands.emplace_back(
            material.shaderHandle,
            sprite.textureHandle,
            material.blendMode,
            vertices
        );
    }

    void QuadBatch::flush(const math::Matrix4f& viewProjectionMatrix)
    {
        if (m_drawCommands.empty())
            return;

        buildBatch(viewProjectionMatrix);

        m_drawCommands.clear();
        m_renderStatistics.batchFlushCount++;
    }

    void QuadBatch::buildBatch(const math::Matrix4f& viewProjectionMatrix)
    {
        uint32_t batchCounter{ 0 };
        BatchData batchData
        {
            .shaderHandle =  m_drawCommands[0].shaderHandle,
            .blendMode = m_drawCommands[0].blendMode,
        };

        for (QuadDrawCommand& command : m_drawCommands)
        {
            auto texSlotActiveEnd = batchData.textureSlots.data.begin() + batchData.textureSlots.count;
            auto texSlotIterator = std::find_if(
                batchData.textureSlots.data.begin(),
                texSlotActiveEnd,
                [&](const TextureHandle& textureHandle)
                {
                    return textureHandle.id == command.textureHandle.id;
                }
            );

            if (command.shaderHandle.id != batchData.shaderHandle.id ||
                command.blendMode != batchData.blendMode ||
                (texSlotIterator == texSlotActiveEnd && batchData.textureSlots.count == TextureSlots::maxCount) ||
                batchCounter == m_maxQuadCount)
            {
                executeBatch(batchData, viewProjectionMatrix);
                batchCounter = 0;
                batchData.textureSlots.count = 0;
                batchData.vertices.clear();
                texSlotActiveEnd = batchData.textureSlots.data.begin();
                texSlotIterator = texSlotActiveEnd;
                batchData.blendMode = command.blendMode;
                batchData.shaderHandle = command.shaderHandle;
            }

            uint32_t currentTexSlotIndex;
            if (texSlotIterator == texSlotActiveEnd)
            {
                currentTexSlotIndex = batchData.textureSlots.count;
                batchData.textureSlots.data[batchData.textureSlots.count] = command.textureHandle;
                batchData.textureSlots.count++;
            }
            else
            {
                currentTexSlotIndex = static_cast<uint32_t>(
                    texSlotIterator - batchData.textureSlots.data.begin()
                );
            }

            for (auto& quadVertex : command.vertices)
            {
                quadVertex.texIndex = currentTexSlotIndex;
            }

            batchData.vertices.insert(batchData.vertices.end(),
                                 command.vertices.begin(),
                                 command.vertices.end()
            );
            batchCounter++;
        }

        if (!batchData.vertices.empty())
        {
            executeBatch(batchData, viewProjectionMatrix);
            batchData.vertices.clear();
        }
    }

    void QuadBatch::executeBatch(
        const BatchData& batchData,
        const math::Matrix4f& viewProjectionMatrix) const
    {
        const Shader& shader = m_shaderManager.get(batchData.shaderHandle);
        const std::array samplerUnits = createSamplerUnits();

        m_graphicsDevice.setBlendMode(batchData.blendMode);
        m_vbo->setData(
            batchData.vertices.data(),
            static_cast<uint32_t>(batchData.vertices.size() * sizeof(QuadVertex))
        );
        shader.bind();
        shader.setMatrix4("u_ViewProjection", viewProjectionMatrix);
        shader.setIntArray(
            "u_Textures",
            samplerUnits.data(),
            samplerUnits.size()
        );

        std::array<math::Vector2f, TextureSlots::maxCount> textureHalfTexels{};
        for (uint32_t i = 0; i < batchData.textureSlots.count; ++i)
        {
            const Texture2D& texture = m_textureManager.get(batchData.textureSlots.data[i]);
            textureHalfTexels[i] =
            {
                0.5f / static_cast<float>(texture.getWidth()),
                0.5f / static_cast<float>(texture.getHeight())
            };
            texture.bind(i);
        }

        shader.setVector2fArray(
            "u_HalfTexels",
            textureHalfTexels.data(),
            static_cast<int>(batchData.textureSlots.count)
        );

        const auto quadCount = static_cast<uint32_t>(batchData.vertices.size() / 4);
        const uint32_t indexCount = quadCount * 6;
        m_graphicsDevice.drawIndexed(*m_vao, indexCount);
        shader.unbind();

        m_renderStatistics.vertexCount += quadCount * 4;
        m_renderStatistics.indexCount += indexCount;
        m_renderStatistics.drawCount++;
    }

    std::array<int, QuadBatch::TextureSlots::maxCount> QuadBatch::createSamplerUnits()
    {
        std::array<int, TextureSlots::maxCount> units{};
        for (uint32_t i = 0; i < TextureSlots::maxCount; ++i)
        {
            units[i] = static_cast<int>(i);
        }

        return units;
    }

    std::array<QuadBatch::QuadVertex, 4> QuadBatch::buildVertices(
        const math::Matrix4f& modelMatrix,
        const math::Vector4f& color,
        const math::Vector2f& minUV,
        const math::Vector2f& maxUV,
        const math::Vector2f& tilingFactor,
        const bool flipVertical,
        const bool flipHorizontal)
    {
        // Transform the quad's local-space corners into world space.
        const math::Vector4f worldBottomLeft =
            modelMatrix * math::Vector4f{-0.5f, -0.5f, 0.0f, 1.0f };

        const math::Vector4f worldBottomRight =
            modelMatrix * math::Vector4f{ 0.5f, -0.5f, 0.0f, 1.0f };

        const math::Vector4f worldTopRight =
            modelMatrix * math::Vector4f{ 0.5f, 0.5f, 0.0f, 1.0f };

        const math::Vector4f worldTopLeft =
            modelMatrix * math::Vector4f{ -0.5f, 0.5f, 0.0f, 1.0f };

        math::Vector2f bottomLeftUV(0.0f, 0.0f);
        math::Vector2f bottomRightUV(1.0f, 0.0f);
        math::Vector2f topRightUV(1.0f, 1.0f);
        math::Vector2f topLeftUV(0.0f, 1.0f);

        if (flipHorizontal)
        {
            bottomLeftUV.x = 1.0f - bottomLeftUV.x;
            bottomRightUV.x = 1.0f - bottomRightUV.x;
            topLeftUV.x = 1.0f - topLeftUV.x;
            topRightUV.x = 1.0f - topRightUV.x;
        }
        if (flipVertical)
        {
            bottomLeftUV.y  = 1.0f - bottomLeftUV.y;
            bottomRightUV.y = 1.0f - bottomRightUV.y;
            topLeftUV.y = 1.0f - topLeftUV.y;
            topRightUV.y = 1.0f - topRightUV.y;
        }

        return{
            // Bottom-Left
            QuadVertex
            {
                { worldBottomLeft.x, worldBottomLeft.y, worldBottomLeft.z},
                bottomLeftUV,
                minUV,
                maxUV,
                tilingFactor,
                color,
                0,
            },
            // Bottom-Right
            QuadVertex
            {
                { worldBottomRight.x, worldBottomRight.y, worldBottomRight.z },
                bottomRightUV,
                minUV,
                maxUV,
                tilingFactor,
                color,
                0,
            },
            // Top-Right
            QuadVertex
            {
                {worldTopRight.x, worldTopRight.y, worldTopRight.z},
                topRightUV,
                minUV,
                maxUV,
                tilingFactor,
                color,
                0,
            },
            // Top-Left
            QuadVertex
            {
                {worldTopLeft.x, worldTopLeft.y, worldTopLeft.z},
                topLeftUV,
                minUV,
                maxUV,
                tilingFactor,
                color,
                0,
            }
        };
    }
}
