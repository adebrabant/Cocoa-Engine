#pragma once

#include "Core/Memory.hpp"
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
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class RenderStatistics;
    struct Material;

    class QuadBatch
    {
    public:
        QuadBatch(
            GraphicsDevice& graphicsDevice,
            ShaderManager& shaderManager,
            TextureManager& textureManager,
            MaterialManager& materialManager,
            RenderStatistics& renderStatistics
        );
        ~QuadBatch();

        void Draw(const Math::Matrix4f& modelMatrix, MaterialHandle materialHandle);
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
            const Material& MaterialRef;
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

    private:
        GraphicsDevice& m_graphicsDevice;
        ShaderManager& m_shaderManager;
        TextureManager& m_textureManager;
        MaterialManager& m_materialManager;
        RenderStatistics& m_renderStatistics;
        Unique<VertexArray> m_vao{ nullptr };
        Unique<VertexBuffer> m_vbo{ nullptr };
        Unique<IndexBuffer> m_ibo{ nullptr};
        std::vector<QuadDrawCommand> m_drawCommands;
        uint32_t m_maxQuadCount;
    };
}