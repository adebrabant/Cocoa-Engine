#pragma once

#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/BlendMode.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/VertexArray.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/Texture2D.hpp>
#include <Graphics/TextureSpec.hpp>

#include "StubFramebuffer.hpp"
#include "StubShader.hpp"
#include "StubIndexBuffer.hpp"
#include "StubVertexArray.hpp"
#include "StubVertexBuffer.hpp"
#include "StubTexture2D.hpp"

namespace CocoaBenchmarks
{
    class StubGraphicsDevice final : public Cocoa::Graphics::GraphicsDevice
    {
    public:
        StubGraphicsDevice() : m_viewport(0, 0, 1920, 1080) { }
        ~StubGraphicsDevice() override = default;

        void BeginFrame() override { }

        void EndFrame() override { }

        void SetBlendMode(Cocoa::Graphics::BlendMode mode) override { }

        void SetViewport(
            int32_t x,
            int32_t y,
            uint32_t width,
            uint32_t height) override { }

        [[nodiscard]] const Cocoa::Graphics::Viewport& GetViewport() const override { return m_viewport; }

        void SetClearColor(
            float red,
            float green,
            float blue,
            float alpha) override { }

        void Clear() override { }

        Cocoa::Unique<Cocoa::Graphics::Shader> CreateShader(
            const std::string& vertexSource,
            const std::string& fragmentSource) override
        {
            return Cocoa::CreateUnique<StubShader>();
        }

        Cocoa::Unique<Cocoa::Graphics::VertexArray> CreateVertexArray() override
        {
            return Cocoa::CreateUnique<StubVertexArray>();
        }

        Cocoa::Unique<Cocoa::Graphics::VertexBuffer> CreateVertexBuffer(
            uint32_t size,
            const Cocoa::Graphics::BufferLayout& bufferLayout) override
        {
            return Cocoa::CreateUnique<StubVertexBuffer>(size, bufferLayout);
        }

        Cocoa::Unique<Cocoa::Graphics::VertexBuffer> CreateVertexBuffer(
            const void* vertices,
            uint32_t size,
            const Cocoa::Graphics::BufferLayout& bufferLayout) override
        {
            return Cocoa::CreateUnique<StubVertexBuffer>(vertices, size, bufferLayout);
        }

        Cocoa::Unique<Cocoa::Graphics::IndexBuffer> CreateIndexBuffer(
            const uint32_t* indices,
            uint32_t count) override
        {
            return Cocoa::CreateUnique<StubIndexBuffer>(indices, count);
        }

        Cocoa::Unique<Cocoa::Graphics::Texture2D> CreateTexture2D(
            Cocoa::Graphics::TextureSpec textureSpec,
            const unsigned char* pixels) override
        {
            return Cocoa::CreateUnique<StubTexture2D>(textureSpec, pixels);
        }

        Cocoa::Unique<Cocoa::Graphics::Framebuffer> CreateFramebuffer(
            const Cocoa::Graphics::FramebufferSpec& framebufferSpec) override
        {
            return Cocoa::CreateUnique<StubFramebuffer>(framebufferSpec);
        }

        void DrawIndexed(const Cocoa::Graphics::VertexArray& vertexArray, uint32_t indexCount) override { }

    private:
        Cocoa::Graphics::Viewport m_viewport;
    };
}
