#pragma once

#include "graphics/BlendMode.hpp"
#include "utilities/Memory.hpp"

#include <cstdint>
#include <string>

namespace cocoa::graphics
{
    class Shader;
    class IndexBuffer;
    class VertexArray;
    class VertexBuffer;
    class Texture2D;
    class BufferLayout;
    struct TextureSpec;
    struct Viewport;
    class Framebuffer;
    struct FramebufferSpec;

    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = default;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual void setBlendMode(BlendMode mode) = 0;
        virtual void setViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) = 0;
        [[nodiscard]] virtual const Viewport& getViewport() const = 0;
        virtual void setClearColor(float red, float green, float blue, float alpha) = 0;
        virtual void clear() = 0;

        virtual Unique<Shader> createShader(const std::string& vertexSource, const std::string& fragmentSource) = 0;
        virtual Unique<VertexArray> createVertexArray() = 0;
        virtual Unique<VertexBuffer> createVertexBuffer(uint32_t size, const BufferLayout& bufferLayout) = 0;
        virtual Unique<VertexBuffer> createVertexBuffer(const void* vertices, uint32_t size, const BufferLayout& bufferLayout) = 0;
        virtual Unique<IndexBuffer> createIndexBuffer(const uint32_t* indices, uint32_t count) = 0;
        virtual Unique<Texture2D> createTexture2D(TextureSpec textureSpec, const unsigned char* pixels) = 0;
        virtual Unique<Framebuffer> createFramebuffer(const FramebufferSpec& framebufferSpec) = 0;

        virtual void drawIndexed(const VertexArray& vertexArray, uint32_t indexCount) = 0;
        // ToDo:
        // virtual void drawLines(const VertexArray& vertexArray, uint32_t vertexCount) = 0;
    };
}
