#pragma once

#include "Math/Vector3f.hpp"
#include "Math/Vector4f.hpp"
#include "Math/Matrix4f.hpp"
#include "Utilities/Memory.hpp"
#include "Graphics/BlendMode.hpp"
#include "Graphics/GraphicsHandles.hpp"
#include <vector>
#include <array>

namespace Cocoa::Graphics
{
    class GraphicsDevice;
    class MaterialManager;
    class ShaderManager;
    class RenderStatistics;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;

    class CircleBatch
    {
    public:
        CircleBatch(
            GraphicsDevice& graphicsDevice,
            MaterialManager& materialManager,
            ShaderManager& shaderManager,
            RenderStatistics& renderStats
        );
        ~CircleBatch();

        void Draw(
            const Math::Matrix4f& modelMatrix,
            MaterialHandle materialHandle,
            const Math::Vector4f& color,
            float thickness,
            float fade
        );

        void Flush(const Math::Matrix4f& viewProjectionMatrix);

    private:
        struct CircleVertex
        {
            Math::Vector3f WorldPosition{};
            Math::Vector2f LocalPosition{};
            Math::Vector4f Color{};
            float Thickness{};
            float Fade{};
        };
        struct CircleDrawCommand
        {
            ShaderHandle Shader{};
            BlendMode Blend{};
            std::array<CircleVertex, 4> Vertices{};
        };
        struct CircleBatchData
        {
            ShaderHandle Shader;
            BlendMode Blend;
            std::vector<CircleVertex> Vertices;
        };
        void BuildBatch(const Math::Matrix4f& viewProjectionMatrix) const;
        void ExecuteBatch(
            const CircleBatchData& batchData,
            const Math::Matrix4f& viewProjectionMatrix) const;

    private:
        GraphicsDevice& m_graphicsDevice;
        MaterialManager& m_materialManager;
        ShaderManager& m_shaderManager;
        RenderStatistics& m_renderStatistics;
        Unique<VertexArray> m_vao{ nullptr };
        Unique<VertexBuffer> m_vbo{ nullptr };
        Unique<IndexBuffer> m_ibo{ nullptr };
        std::vector<CircleDrawCommand> m_drawCommands;
        uint32_t m_maxCircleCount;
    };
}
