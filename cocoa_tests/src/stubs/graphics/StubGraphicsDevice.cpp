#include "stubs/Graphics/StubGraphicsDevice.hpp"
#include "stubs/Graphics/StubFramebuffer.hpp"
#include "stubs/Graphics/StubIndexBuffer.hpp"
#include "stubs/Graphics/StubShader.hpp"
#include "stubs/Graphics/StubTexture2D.hpp"
#include "stubs/Graphics/StubVertexArray.hpp"
#include "stubs/Graphics/StubVertexBuffer.hpp"

#include <graphics/BufferElement.hpp>
#include <graphics/BufferLayout.hpp>
#include <graphics/IndexBuffer.hpp>
#include <graphics/TextureSpec.hpp>
#include <graphics/VertexArray.hpp>
#include <graphics/VertexBuffer.hpp>
#include <utilities/Memory.hpp>

namespace CocoaTests::Stubs
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

	void StubGraphicsDevice::SetBlendMode(cocoa::Graphics::BlendMode mode)
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

	cocoa::Unique<cocoa::Graphics::Shader> StubGraphicsDevice::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		return cocoa::CreateUnique<StubShader>();
	}

	cocoa::Unique<cocoa::Graphics::VertexArray> StubGraphicsDevice::CreateVertexArray()
	{
		return cocoa::CreateUnique<StubVertexArray>();
	}

	cocoa::Unique<cocoa::Graphics::VertexBuffer> StubGraphicsDevice::CreateVertexBuffer(
		uint32_t size, const cocoa::Graphics::BufferLayout& bufferLayout)
	{
		return cocoa::CreateUnique<StubVertexBuffer>(size, bufferLayout, m_vertexBufferCapture);
	}

	cocoa::Unique<cocoa::Graphics::VertexBuffer> StubGraphicsDevice::CreateVertexBuffer(
		const void* vertices, uint32_t size, const cocoa::Graphics::BufferLayout& bufferLayout)
	{
		return cocoa::CreateUnique<StubVertexBuffer>(vertices, size, bufferLayout, m_vertexBufferCapture);
	}

	cocoa::Unique<cocoa::Graphics::IndexBuffer> StubGraphicsDevice::CreateIndexBuffer(const uint32_t* indices, uint32_t count)
	{
		return cocoa::CreateUnique<StubIndexBuffer>(indices, count);
	}

	cocoa::Unique<cocoa::Graphics::Texture2D> StubGraphicsDevice::CreateTexture2D(cocoa::Graphics::TextureSpec textureSpec, const unsigned char* pixels)
	{
		return cocoa::CreateUnique<StubTexture2D>();
	}

	cocoa::Unique<cocoa::Graphics::Framebuffer> StubGraphicsDevice::CreateFramebuffer(const cocoa::Graphics::FramebufferSpec& framebufferSpec)
	{
		return cocoa::CreateUnique<StubFramebuffer>(framebufferSpec);
	}

	void StubGraphicsDevice::DrawIndexed(const cocoa::Graphics::VertexArray& vertexArray, uint32_t indexCount)
	{

	}
}
