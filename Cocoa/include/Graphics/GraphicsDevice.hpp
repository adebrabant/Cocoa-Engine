#pragma once

#include "Core/Memory.hpp"
#include <string>
#include <cstdint>

namespace Cocoa::Graphics
{
    class Shader;
    class IndexBuffer;
    class VertexArray;
    class VertexBuffer;
    class Texture2D;
    class BufferLayout;
    struct TextureSpec;

    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = default;
        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;
        virtual void SetViewport(uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(float red, float green, float blue, float alpha) = 0;
        virtual void Clear() = 0;

        virtual Unique<Shader> CreateShader(const std::string& vertexSource, const std::string& fragmentSource) = 0;
        virtual Unique<VertexArray> CreateVertexArray() = 0;
        virtual Unique<VertexBuffer> CreateVertexBuffer(const float* vertices, uint32_t size, const BufferLayout& bufferLayout) = 0;
        virtual Unique<IndexBuffer> CreateIndexBuffer(const uint32_t* indices, uint32_t count) = 0;
        virtual Unique<Texture2D> CreateTexture2D(TextureSpec textureSpec, const unsigned char* pixels) = 0;

        virtual void DrawIndexed(const VertexArray& vertexArray, uint32_t indexCount) = 0;
        // ToDo:
        // virtual void DrawLines(const VertexArray& vertexArray, uint32_t vertexCount) = 0;
    };
}