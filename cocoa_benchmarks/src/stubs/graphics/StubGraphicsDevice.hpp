#pragma once

#include <graphics/BlendMode.hpp>
#include <graphics/GraphicsDevice.hpp>
#include <graphics/IndexBuffer.hpp>
#include <graphics/Shader.hpp>
#include <graphics/Texture2D.hpp>
#include <graphics/TextureSpec.hpp>
#include <graphics/VertexArray.hpp>
#include <graphics/VertexBuffer.hpp>

#include "StubFramebuffer.hpp"
#include "StubIndexBuffer.hpp"
#include "StubShader.hpp"
#include "StubTexture2D.hpp"
#include "StubVertexArray.hpp"
#include "StubVertexBuffer.hpp"

namespace CocoaBenchmarks
{
    class StubGraphicsDevice final : public cocoa::Graphics::GraphicsDevice
    {
    public:
        StubGraphicsDevice() : m_viewport(0, 0, 1920, 1080) { }
        ~StubGraphicsDevice() override = default;

        void BeginFrame() override { }

        void EndFrame() override { }

        void SetBlendMode(cocoa::Graphics::BlendMode mode) override { }

        void SetViewport(
            int32_t x,
            int32_t y,
            uint32_t width,
            uint32_t height) override { }

        [[nodiscard]] const cocoa::Graphics::Viewport& GetViewport() const override { return m_viewport; }

        void SetClearColor(
            float red,
            float green,
            float blue,
            float alpha) override { }

        void Clear() override { }

        cocoa::Unique<cocoa::Graphics::Shader> CreateShader(
            const std::string& vertexSource,
            const std::string& fragmentSource) override
        {
            return cocoa::CreateUnique<StubShader>();
        }

        cocoa::Unique<cocoa::Graphics::VertexArray> CreateVertexArray() override
        {
            return cocoa::CreateUnique<StubVertexArray>();
        }

        cocoa::Unique<cocoa::Graphics::VertexBuffer> CreateVertexBuffer(
            uint32_t size,
            const cocoa::Graphics::BufferLayout& bufferLayout) override
        {
            return cocoa::CreateUnique<StubVertexBuffer>(size, bufferLayout);
        }

        cocoa::Unique<cocoa::Graphics::VertexBuffer> CreateVertexBuffer(
            const void* vertices,
            uint32_t size,
            const cocoa::Graphics::BufferLayout& bufferLayout) override
        {
            return cocoa::CreateUnique<StubVertexBuffer>(vertices, size, bufferLayout);
        }

        cocoa::Unique<cocoa::Graphics::IndexBuffer> CreateIndexBuffer(
            const uint32_t* indices,
            uint32_t count) override
        {
            return cocoa::CreateUnique<StubIndexBuffer>(indices, count);
        }

        cocoa::Unique<cocoa::Graphics::Texture2D> CreateTexture2D(
            cocoa::Graphics::TextureSpec textureSpec,
            const unsigned char* pixels) override
        {
            return cocoa::CreateUnique<StubTexture2D>(textureSpec, pixels);
        }

        cocoa::Unique<cocoa::Graphics::Framebuffer> CreateFramebuffer(
            const cocoa::Graphics::FramebufferSpec& framebufferSpec) override
        {
            return cocoa::CreateUnique<StubFramebuffer>(framebufferSpec);
        }

        void DrawIndexed(const cocoa::Graphics::VertexArray& vertexArray, uint32_t indexCount) override { }

    private:
        cocoa::Graphics::Viewport m_viewport;
    };
}
