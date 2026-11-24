#pragma once

#include "Math/Vector2f.hpp"
#include "Math/Vector3f.hpp"
#include "Math/Vector4f.hpp"
#include "Math/Matrix4f.hpp"
#include "Utilities/Memory.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/GraphicsHandles.hpp"
#include "Graphics/BlendMode.hpp"
#include <array>
#include <vector>

namespace Cocoa::Graphics
{
    class GraphicsDevice;
    class MaterialManager;
    class ShaderManager;
    class RenderStatistics;

    class LineBatch
    {
    public:
        LineBatch(
            GraphicsDevice& graphicsDevice,
            MaterialManager& materialManager,
            ShaderManager& shaderManager,
            RenderStatistics& renderStats
        );
        void Draw(
            MaterialHandle materialHandle,
            const Math::Matrix4f& modelMatrix,
            const Math::Vector4f& color,
            const Math::Vector2f& startPoint,
            const Math::Vector2f& endPoint,
            float thickness,
            float fade
        );
        void Flush(const Math::Matrix4f& viewProjectionMatrix);

    private:
        struct LineVertex
        {
            Math::Vector3f WorldPosition{};
            Math::Vector2f LocalPosition{};
            Math::Vector4f Color{};
            Math::Vector2f Fade{};
        };
        struct LineDrawCommand
        {
            ShaderHandle Shader{};
            BlendMode Blend{};
            std::array<LineVertex, 4> Vertices{};
        };
        struct LineBatchData
        {
            ShaderHandle Shader;
            BlendMode Blend;
            std::vector<LineVertex> Vertices;
        };
        void BuildBatch(const Math::Matrix4f& viewProjectionMatrix) const;
        void ExecuteBatch(
            const LineBatchData& batchData,
            const Math::Matrix4f& viewProjectionMatrix
        ) const;

    private:
        GraphicsDevice& m_graphicsDevice;
        MaterialManager& m_materialManager;
        ShaderManager& m_shaderManager;
        RenderStatistics& m_renderStats;
        Unique<VertexArray> m_vao{nullptr};
        Unique<VertexBuffer> m_vbo{nullptr};
        Unique<IndexBuffer> m_ibo{nullptr};
        std::vector<LineDrawCommand> m_drawCommands;
        uint32_t m_maxLineCount;
    };
}