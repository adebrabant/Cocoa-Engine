#include "stubs/graphics/StubGraphicsDevice.hpp"
#include "stubs/graphics/StubFramebuffer.hpp"
#include "stubs/graphics/StubIndexBuffer.hpp"
#include "stubs/graphics/StubShader.hpp"
#include "stubs/graphics/StubTexture2D.hpp"
#include "stubs/graphics/StubVertexArray.hpp"
#include "stubs/graphics/StubVertexBuffer.hpp"

#include <graphics/BufferElement.hpp>
#include <graphics/BufferLayout.hpp>
#include <graphics/IndexBuffer.hpp>
#include <graphics/TextureSpec.hpp>
#include <graphics/VertexArray.hpp>
#include <graphics/VertexBuffer.hpp>
#include <utilities/Memory.hpp>

namespace cocoa_tests::stubs
{
	StubGraphicsDevice::StubGraphicsDevice() :
		m_vertexBufferCapture(),
		m_viewport(0, 0, 1920, 1080)
	{

	}

	void StubGraphicsDevice::beginFrame()
	{

	}

	void StubGraphicsDevice::endFrame()
	{
	}

	void StubGraphicsDevice::setBlendMode(cocoa::graphics::BlendMode mode)
	{

	}

	void StubGraphicsDevice::setViewport(int32_t x, int32_t y, uint32_t width, uint32_t height)
	{
		m_viewport.resize(x, y, width, height);
	}

	void StubGraphicsDevice::setClearColor(float red, float green, float blue, float alpha)
	{
	}

	void StubGraphicsDevice::clear()
	{

	}

	cocoa::Unique<cocoa::graphics::Shader> StubGraphicsDevice::createShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		return cocoa::createUnique<StubShader>();
	}

	cocoa::Unique<cocoa::graphics::VertexArray> StubGraphicsDevice::createVertexArray()
	{
		return cocoa::createUnique<StubVertexArray>();
	}

	cocoa::Unique<cocoa::graphics::VertexBuffer> StubGraphicsDevice::createVertexBuffer(
		uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout)
	{
		return cocoa::createUnique<StubVertexBuffer>(size, bufferLayout, m_vertexBufferCapture);
	}

	cocoa::Unique<cocoa::graphics::VertexBuffer> StubGraphicsDevice::createVertexBuffer(
		const void* vertices, uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout)
	{
		return cocoa::createUnique<StubVertexBuffer>(vertices, size, bufferLayout, m_vertexBufferCapture);
	}

	cocoa::Unique<cocoa::graphics::IndexBuffer> StubGraphicsDevice::createIndexBuffer(const uint32_t* indices, uint32_t count)
	{
		return cocoa::createUnique<StubIndexBuffer>(indices, count);
	}

	cocoa::Unique<cocoa::graphics::Texture2D> StubGraphicsDevice::createTexture2D(cocoa::graphics::TextureSpec textureSpec, const unsigned char* pixels)
	{
		return cocoa::createUnique<StubTexture2D>();
	}

	cocoa::Unique<cocoa::graphics::Framebuffer> StubGraphicsDevice::createFramebuffer(const cocoa::graphics::FramebufferSpec& framebufferSpec)
	{
		return cocoa::createUnique<StubFramebuffer>(framebufferSpec);
	}

	void StubGraphicsDevice::drawIndexed(const cocoa::graphics::VertexArray& vertexArray, uint32_t indexCount)
	{

	}
}
