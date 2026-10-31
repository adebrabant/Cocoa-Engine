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

        void Draw(
            const math::Matrix4f& modelMatrix,
            MaterialHandle materialHandle,
            TextureHandle textureHandle,
            const math::Vector2f& tilingFactor
        );
        void Draw(
            const math::Matrix4f& modelMatrix,
            MaterialHandle materialHandle,
            SpriteHandle spriteHandle,
            const math::Vector2f& tilingFactor,
            bool flipVertical,
            bool flipHorizontal
        );
        void Flush(const math::Matrix4f& viewProjectionMatrix);

    private:
        struct QuadVertex
        {
            math::Vector3f Position{};
            math::Vector2f LocalUV{};
            math::Vector2f MinUV{};
            math::Vector2f MaxUV{};
            math::Vector2f TilingFactor{};
            math::Vector4f Color{};
            uint32_t TexIndex{0};
        };
        struct QuadDrawCommand
        {
            ShaderHandle Shader{};
            TextureHandle Texture {};
            BlendMode Blend{};
            std::array<QuadVertex, 4> Vertices{};
        };
        struct TextureSlots
        {
            static constexpr uint32_t MaxCount{32};
            std::array<TextureHandle, MaxCount> Data{};
            uint32_t Count{0};
        };
        struct BatchData
        {
            ShaderHandle Shader;
            TextureSlots Textures;
            BlendMode Blend;
            std::vector<QuadVertex> Vertices;
        };
        void BuildBatch(const math::Matrix4f& viewProjectionMatrix);
        void ExecuteBatch(
            const BatchData& batchData,
            const math::Matrix4f& viewProjectionMatrix
        ) const;
        static std::array<int, TextureSlots::MaxCount> CreateSamplerUnits();
        static std::array<QuadVertex, 4> BuildVertices(
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
