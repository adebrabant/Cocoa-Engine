#pragma once

#include "StubVertexBuffer.hpp"
#include <graphics/GraphicsDevice.hpp>
#include <graphics/Viewport.hpp>

namespace CocoaTests::Stubs
{
	struct VertexBufferCapture;

	class StubGraphicsDevice : public cocoa::Graphics::GraphicsDevice
	{
	public:
		StubGraphicsDevice();
		~StubGraphicsDevice() override = default;
		void BeginFrame() override;
		void EndFrame() override;
		void SetBlendMode(cocoa::Graphics::BlendMode mode) override;
		void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
		[[nodiscard]] const cocoa::Graphics::Viewport& GetViewport() const override { return m_viewport; }
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void Clear() override;
		cocoa::Unique<cocoa::Graphics::Shader> CreateShader(const std::string& vertexSource, const std::string& fragmentSource) override;
		cocoa::Unique<cocoa::Graphics::VertexArray> CreateVertexArray() override;
		cocoa::Unique<cocoa::Graphics::VertexBuffer> CreateVertexBuffer(uint32_t size, const cocoa::Graphics::BufferLayout& bufferLayout) override;
		cocoa::Unique<cocoa::Graphics::VertexBuffer> CreateVertexBuffer(const void* vertices, uint32_t size, const cocoa::Graphics::BufferLayout& bufferLayout) override;
		cocoa::Unique<cocoa::Graphics::IndexBuffer> CreateIndexBuffer(const uint32_t* indices, uint32_t count) override;
		cocoa::Unique<cocoa::Graphics::Texture2D> CreateTexture2D(cocoa::Graphics::TextureSpec textureSpec, const unsigned char* pixels) override;
		cocoa::Unique<cocoa::Graphics::Framebuffer> CreateFramebuffer(const cocoa::Graphics::FramebufferSpec& framebufferSpec) override;
		void DrawIndexed(const cocoa::Graphics::VertexArray& vertexArray, uint32_t indexCount) override;

		[[nodiscard]]const VertexBufferCapture& GetVertexBufferCapture() const { return m_vertexBufferCapture; }

	private:
		VertexBufferCapture m_vertexBufferCapture;
		cocoa::Graphics::Viewport m_viewport;
	};
}