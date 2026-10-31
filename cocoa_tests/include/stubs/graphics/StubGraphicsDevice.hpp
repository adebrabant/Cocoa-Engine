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
		void beginFrame() override;
		void endFrame() override;
		void setBlendMode(cocoa::graphics::BlendMode mode) override;
		void setViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
		[[nodiscard]] const cocoa::graphics::Viewport& getViewport() const override { return m_viewport; }
		void setClearColor(float red, float green, float blue, float alpha) override;
		void clear() override;
		cocoa::Unique<cocoa::graphics::Shader> createShader(const std::string& vertexSource, const std::string& fragmentSource) override;
		cocoa::Unique<cocoa::graphics::VertexArray> createVertexArray() override;
		cocoa::Unique<cocoa::graphics::VertexBuffer> createVertexBuffer(uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout) override;
		cocoa::Unique<cocoa::graphics::VertexBuffer> createVertexBuffer(const void* vertices, uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout) override;
		cocoa::Unique<cocoa::graphics::IndexBuffer> createIndexBuffer(const uint32_t* indices, uint32_t count) override;
		cocoa::Unique<cocoa::graphics::Texture2D> createTexture2D(cocoa::graphics::TextureSpec textureSpec, const unsigned char* pixels) override;
		cocoa::Unique<cocoa::graphics::Framebuffer> createFramebuffer(const cocoa::graphics::FramebufferSpec& framebufferSpec) override;
		void drawIndexed(const cocoa::graphics::VertexArray& vertexArray, uint32_t indexCount) override;

		[[nodiscard]]const VertexBufferCapture& GetVertexBufferCapture() const { return m_vertexBufferCapture; }

	private:
		VertexBufferCapture m_vertexBufferCapture;
		cocoa::graphics::Viewport m_viewport;
	};
}
