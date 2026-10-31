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

	void StubGraphicsDevice::BeginFrame()
	{

	}

	void StubGraphicsDevice::EndFrame()
	{
	}

	void StubGraphicsDevice::SetBlendMode(cocoa::graphics::BlendMode mode)
	{

	}

	void StubGraphicsDevice::SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height)
	{
		m_viewport.Resize(x, y, width, height);
	}

	void StubGraphicsDevice::SetClearColor(float red, float green, float blue, float alpha)
	{
	}

	void StubGraphicsDevice::Clear()
	{

	}

	cocoa::Unique<cocoa::graphics::Shader> StubGraphicsDevice::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		return cocoa::CreateUnique<StubShader>();
	}

	cocoa::Unique<cocoa::graphics::VertexArray> StubGraphicsDevice::CreateVertexArray()
	{
		return cocoa::CreateUnique<StubVertexArray>();
	}

	cocoa::Unique<cocoa::graphics::VertexBuffer> StubGraphicsDevice::CreateVertexBuffer(
		uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout)
	{
		return cocoa::CreateUnique<StubVertexBuffer>(size, bufferLayout, m_vertexBufferCapture);
	}

	cocoa::Unique<cocoa::graphics::VertexBuffer> StubGraphicsDevice::CreateVertexBuffer(
		const void* vertices, uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout)
	{
		return cocoa::CreateUnique<StubVertexBuffer>(vertices, size, bufferLayout, m_vertexBufferCapture);
	}

	cocoa::Unique<cocoa::graphics::IndexBuffer> StubGraphicsDevice::CreateIndexBuffer(const uint32_t* indices, uint32_t count)
	{
		return cocoa::CreateUnique<StubIndexBuffer>(indices, count);
	}

	cocoa::Unique<cocoa::graphics::Texture2D> StubGraphicsDevice::CreateTexture2D(cocoa::graphics::TextureSpec textureSpec, const unsigned char* pixels)
	{
		return cocoa::CreateUnique<StubTexture2D>();
	}

	cocoa::Unique<cocoa::graphics::Framebuffer> StubGraphicsDevice::CreateFramebuffer(const cocoa::graphics::FramebufferSpec& framebufferSpec)
	{
		return cocoa::CreateUnique<StubFramebuffer>(framebufferSpec);
	}

	void StubGraphicsDevice::DrawIndexed(const cocoa::graphics::VertexArray& vertexArray, uint32_t indexCount)
	{

	}
}
