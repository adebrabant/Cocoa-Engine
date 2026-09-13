#pragma once

#include "Utilities/Memory.hpp"
#include "Math/Vector3f.hpp"
#include "Math/Vector2f.hpp"
#include "Math/Vector4f.hpp"
#include "Math/Matrix4f.hpp"
#include "Graphics/GraphicsHandles.hpp"

#include <array>
#include <vector>

namespace Cocoa::Graphics
{
    class GraphicsDevice;
    class ShaderManager;
    class TextureManager;
    class MaterialManager;
    class SpriteManager;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class RenderStatistics;

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
            const Math::Matrix4f& modelMatrix,
            MaterialHandle materialHandle,
            TextureHandle textureHandle
        );
        void Draw(
            const Math::Matrix4f& modelMatrix,
            MaterialHandle materialHandle,
            SpriteHandle spriteHandle
        );
        void Flush(const Math::Matrix4f& viewProjectionMatrix);

    private:
        struct QuadVertex
        {
            Math::Vector3f Position{};
            Math::Vector2f TexCoord{};
            Math::Vector4f Color{};
            uint32_t TexIndex{0};
        };
        struct QuadDrawCommand
        {
            ShaderHandle Shader{};
            TextureHandle Texture {};
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
            std::vector<QuadVertex> Vertices;
        };
        void BuildBatch(const Math::Matrix4f& viewProjectionMatrix);
        void ExecuteBatch(
            const BatchData& batchData,
            const Math::Matrix4f& viewProjectionMatrix
        ) const;
        static std::array<int, TextureSlots::MaxCount> CreateSamplerUnits();
        static std::array<QuadVertex, 4> BuildVertices(
            const Math::Matrix4f& modelMatrix,
            const Math::Vector4f& color,
            const Math::Vector2f& minUV,
            const Math::Vector2f& maxUV
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