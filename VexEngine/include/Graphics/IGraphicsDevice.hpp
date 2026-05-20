#pragma once
#include <cstdint>

namespace VexEngine::Graphics
{
    class IGraphicsDevice
    {
    public:
        virtual ~IGraphicsDevice() = default;
        virtual void SetViewport(uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(float red, float green, float blue, float alpha) = 0;
        virtual void Clear() = 0;

        // ToDo:
        // virtual void DrawIndexed(const VertexArray& vertexArray, uint32_t indexCount = 0) = 0;
        // virtual void DrawLines(const VertexArray& vertexArray, uint32_t vertexCount) = 0;
    };
}