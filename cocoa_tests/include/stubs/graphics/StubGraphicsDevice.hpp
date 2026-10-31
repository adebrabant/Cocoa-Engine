#pragma once

#include "StubVertexBuffer.hpp"
#include <graphics/GraphicsDevice.hpp>
#include <graphics/Viewport.hpp>

namespace cocoa_tests::stubs
{
	struct VertexBufferCapture;

	class StubGraphicsDevice : public cocoa::graphics::GraphicsDevice
	{
	public:
		StubGraphicsDevice();
		~StubGraphicsDevice() override = default;
		void BeginFrame() override;
		void EndFrame() override;
		void SetBlendMode(cocoa::graphics::BlendMode mode) override;
		void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
		[[nodiscard]] const cocoa::graphics::Viewport& GetViewport() const override { return m_viewport; }
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void Clear() override;
		cocoa::Unique<cocoa::graphics::Shader> CreateShader(const std::string& vertexSource, const std::string& fragmentSource) override;
		cocoa::Unique<cocoa::graphics::VertexArray> CreateVertexArray() override;
		cocoa::Unique<cocoa::graphics::VertexBuffer> CreateVertexBuffer(uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout) override;
		cocoa::Unique<cocoa::graphics::VertexBuffer> CreateVertexBuffer(const void* vertices, uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout) override;
		cocoa::Unique<cocoa::graphics::IndexBuffer> CreateIndexBuffer(const uint32_t* indices, uint32_t count) override;
		cocoa::Unique<cocoa::graphics::Texture2D> CreateTexture2D(cocoa::graphics::TextureSpec textureSpec, const unsigned char* pixels) override;
		cocoa::Unique<cocoa::graphics::Framebuffer> CreateFramebuffer(const cocoa::graphics::FramebufferSpec& framebufferSpec) override;
		void DrawIndexed(const cocoa::graphics::VertexArray& vertexArray, uint32_t indexCount) override;

		[[nodiscard]]const VertexBufferCapture& GetVertexBufferCapture() const { return m_vertexBufferCapture; }

	private:
		VertexBufferCapture m_vertexBufferCapture;
		cocoa::graphics::Viewport m_viewport;
	};
}
