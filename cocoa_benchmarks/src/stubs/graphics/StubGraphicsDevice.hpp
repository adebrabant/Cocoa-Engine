#pragma once

#include <graphics/BlendMode.hpp>
#include <graphics/GraphicsDevice.hpp>
#include <graphics/IndexBuffer.hpp>
#include <graphics/Shader.hpp>
#include <graphics/Texture2D.hpp>
#include <graphics/TextureSpec.hpp>
#include <graphics/VertexArray.hpp>
#include <graphics/VertexBuffer.hpp>
#include <graphics/Viewport.hpp>

#include "StubFramebuffer.hpp"
#include "StubIndexBuffer.hpp"
#include "StubShader.hpp"
#include "StubTexture2D.hpp"
#include "StubVertexArray.hpp"
#include "StubVertexBuffer.hpp"

namespace cocoa_benchmarks
{
    class StubGraphicsDevice final : public cocoa::graphics::GraphicsDevice
    {
    public:
        StubGraphicsDevice() : m_viewport(0, 0, 1920, 1080) { }
        ~StubGraphicsDevice() override = default;

        void beginFrame() override { }

        void endFrame() override { }

        void setBlendMode(cocoa::graphics::BlendMode mode) override { }

        void setViewport(
            int32_t x,
            int32_t y,
            uint32_t width,
            uint32_t height) override { }

        [[nodiscard]] const cocoa::graphics::Viewport& getViewport() const override { return m_viewport; }

        void setClearColor(
            float red,
            float green,
            float blue,
            float alpha) override { }

        void clear() override { }

        cocoa::Unique<cocoa::graphics::Shader> createShader(
            const std::string& vertexSource,
            const std::string& fragmentSource) override
        {
            return cocoa::createUnique<StubShader>();
        }

        cocoa::Unique<cocoa::graphics::VertexArray> createVertexArray() override
        {
            return cocoa::createUnique<StubVertexArray>();
        }

        cocoa::Unique<cocoa::graphics::VertexBuffer> createVertexBuffer(
            uint32_t size,
            const cocoa::graphics::BufferLayout& bufferLayout) override
        {
            return cocoa::createUnique<StubVertexBuffer>(size, bufferLayout);
        }

        cocoa::Unique<cocoa::graphics::VertexBuffer> createVertexBuffer(
            const void* vertices,
            uint32_t size,
            const cocoa::graphics::BufferLayout& bufferLayout) override
        {
            return cocoa::createUnique<StubVertexBuffer>(vertices, size, bufferLayout);
        }

        cocoa::Unique<cocoa::graphics::IndexBuffer> createIndexBuffer(
            const uint32_t* indices,
            uint32_t count) override
        {
            return cocoa::createUnique<StubIndexBuffer>(indices, count);
        }

        cocoa::Unique<cocoa::graphics::Texture2D> createTexture2D(
            cocoa::graphics::TextureSpec textureSpec,
            const unsigned char* pixels) override
        {
            return cocoa::createUnique<StubTexture2D>(textureSpec, pixels);
        }

        cocoa::Unique<cocoa::graphics::Framebuffer> createFramebuffer(
            const cocoa::graphics::FramebufferSpec& framebufferSpec) override
        {
            return cocoa::createUnique<StubFramebuffer>(framebufferSpec);
        }

        void drawIndexed(const cocoa::graphics::VertexArray& vertexArray, uint32_t indexCount) override { }

    private:
        cocoa::graphics::Viewport m_viewport;
    };
}
