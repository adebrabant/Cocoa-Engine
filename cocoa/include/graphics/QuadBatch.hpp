#pragma once

#include "graphics/BlendMode.hpp"
#include "graphics/GraphicsHandles.hpp"
#include "math/Matrix4f.hpp"
#include "math/Vector2f.hpp"
#include "math/Vector3f.hpp"
#include "math/Vector4f.hpp"
#include "utilities/Memory.hpp"

#include <array>
#include <vector>

namespace cocoa::graphics
{
    class GraphicsDevice;
    class ShaderManager;
    class TextureManager;
    class MaterialManager;
    class SpriteManager;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    struct RenderStatistics;

    class QuadBatch
    {
    public:
        QuadBatch(
            GraphicsDevice& graphicsDevice,
            ShaderManager& shaderManager,
            TextureManager& textureManager,
            MaterialManager& materialManager,
            SpriteManager& spriteManager,
            RenderStatistics& renderStatistics
        );
        ~QuadBatch();

        void draw(
            const math::Matrix4f& modelMatrix,
            MaterialHandle materialHandle,
            TextureHandle textureHandle,
            const math::Vector2f& tilingFactor
        );
        void draw(
            const math::Matrix4f& modelMatrix,
            MaterialHandle materialHandle,
            SpriteHandle spriteHandle,
            const math::Vector2f& tilingFactor,
            bool flipVertical,
            bool flipHorizontal
        );
        void flush(const math::Matrix4f& viewProjectionMatrix);

    private:
        struct QuadVertex
        {
            math::Vector3f position{};
            math::Vector2f localUV{};
            math::Vector2f minUV{};
            math::Vector2f MaxUV{};
            math::Vector2f tilingFactor{};
            math::Vector4f color{};
            uint32_t texIndex{0};
        };
        struct QuadDrawCommand
        {
            ShaderHandle shaderHandle{};
            TextureHandle textureHandle {};
            BlendMode blendMode{};
            std::array<QuadVertex, 4> vertices{};
        };
        struct TextureSlots
        {
            static constexpr uint32_t maxCount{32};
            std::array<TextureHandle, maxCount> data{};
            uint32_t count{0};
        };
        struct BatchData
        {
            ShaderHandle shaderHandle;
            TextureSlots textureSlots;
            BlendMode blendMode;
            std::vector<QuadVertex> vertices;
        };
        void buildBatch(const math::Matrix4f& viewProjectionMatrix);
        void executeBatch(
            const BatchData& batchData,
            const math::Matrix4f& viewProjectionMatrix
        ) const;
        static std::array<int, TextureSlots::maxCount> createSamplerUnits();
        static std::array<QuadVertex, 4> buildVertices(
            const math::Matrix4f& modelMatrix,
            const math::Vector4f& color,
            const math::Vector2f& minUV,
            const math::Vector2f& maxUV,
            const math::Vector2f& tilingFactor,
            bool flipVertical,
            bool flipHorizontal
        );

    private:
        GraphicsDevice& m_graphicsDevice;
        ShaderManager& m_shaderManager;
        TextureManager& m_textureManager;
        MaterialManager& m_materialManager;
        SpriteManager& m_spriteManager;
        RenderStatistics& m_renderStatistics;
        Unique<VertexArray> m_vao{ nullptr };
        Unique<VertexBuffer> m_vbo{ nullptr };
        Unique<IndexBuffer> m_ibo{ nullptr};
        std::vector<QuadDrawCommand> m_drawCommands;
        uint32_t m_maxQuadCount;
    };
}
