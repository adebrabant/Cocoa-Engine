#pragma once

#include "graphics/GraphicsDevice.hpp"
#include "graphics/Viewport.hpp"
#include "utilities/Memory.hpp"

#include <cstdint>

namespace cocoa::graphics
{
	class OpenGLGraphicsDevice : public GraphicsDevice
	{
	public:
		OpenGLGraphicsDevice();
		~OpenGLGraphicsDevice() override;
		void beginFrame() override;
		void endFrame() override;
		void setBlendMode(BlendMode mode) override;
		void setViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
		[[nodiscard]] const Viewport& getViewport() const override { return m_viewport; }
		void setClearColor(float red, float green, float blue, float alpha) override;
		void clear() override;

		Unique<Shader> createShader(const std::string& vertexSource, const std::string& fragmentSource) override;
		Unique<VertexArray> createVertexArray() override;
		Unique<VertexBuffer> createVertexBuffer(uint32_t size, const BufferLayout& bufferLayout) override;
		Unique<VertexBuffer> createVertexBuffer(const void* vertices, uint32_t size, const BufferLayout& bufferLayout) override;
		Unique<IndexBuffer> createIndexBuffer(const uint32_t* indices, uint32_t count) override;
		Unique<Texture2D> createTexture2D(TextureSpec textureSpec, const unsigned char* pixels) override;
		Unique<Framebuffer> createFramebuffer(const FramebufferSpec& framebufferSpec) override;

		void drawIndexed(const VertexArray& vertexArray, uint32_t indexCount) override;

	private:
		Viewport m_viewport;
	};
}
