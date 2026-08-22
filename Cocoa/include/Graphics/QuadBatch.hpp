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
        };
        struct QuadDrawCommand
        {
            MaterialHandle Material{};
            std::array<QuadVertex, 4> Vertices{};
        };
        void FlushBatch(
            const MaterialHandle& handle,
            const Math::Matrix4f& viewProjectionMatrix,
            const std::vector<QuadVertex>& batchVertices) const;

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