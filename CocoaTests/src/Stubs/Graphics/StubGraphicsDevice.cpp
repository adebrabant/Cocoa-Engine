#include "Stubs/Graphics/StubGraphicsDevice.hpp"
#include "Stubs/Graphics/StubVertexArray.hpp"
#include "Stubs/Graphics/StubShader.hpp"
#include "Stubs/Graphics/StubTexture2D.hpp"
#include "Stubs/Graphics/StubVertexBuffer.hpp"
#include "Stubs/Graphics/StubIndexBuffer.hpp"

#include <Graphics/IndexBuffer.hpp>
#include <Graphics/TextureSpec.hpp>
#include <Graphics/BufferElement.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexArray.hpp>
#include <Graphics/BufferLayout.hpp>
#include <Utilities/Memory.hpp>

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

	void StubGraphicsDevice::SetBlendMode(Cocoa::Graphics::BlendMode mode)
	{

	}

	void StubGraphicsDevice::SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height)
	{

	}

	void StubGraphicsDevice::SetClearColor(float red, float green, float blue, float alpha)
	{
	}

	void StubGraphicsDevice::Clear()
	{

	}

	Cocoa::Unique<Cocoa::Graphics::Shader> StubGraphicsDevice::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		return Cocoa::CreateUnique<StubShader>();
	}

	Cocoa::Unique<Cocoa::Graphics::VertexArray> StubGraphicsDevice::CreateVertexArray()
	{
		return Cocoa::CreateUnique<StubVertexArray>();
	}

	Cocoa::Unique<Cocoa::Graphics::VertexBuffer> StubGraphicsDevice::CreateVertexBuffer(
		uint32_t size, const Cocoa::Graphics::BufferLayout& bufferLayout)
	{
		return Cocoa::CreateUnique<StubVertexBuffer>(size, bufferLayout, m_vertexBufferCapture);
	}

	Cocoa::Unique<Cocoa::Graphics::VertexBuffer> StubGraphicsDevice::CreateVertexBuffer(
		const void* vertices, uint32_t size, const Cocoa::Graphics::BufferLayout& bufferLayout)
	{
		return Cocoa::CreateUnique<StubVertexBuffer>(vertices, size, bufferLayout, m_vertexBufferCapture);
	}

	Cocoa::Unique<Cocoa::Graphics::IndexBuffer> StubGraphicsDevice::CreateIndexBuffer(const uint32_t* indices, uint32_t count)
	{
		return Cocoa::CreateUnique<StubIndexBuffer>(indices, count);
	}

	Cocoa::Unique<Cocoa::Graphics::Texture2D> StubGraphicsDevice::CreateTexture2D(Cocoa::Graphics::TextureSpec textureSpec, const unsigned char* pixels)
	{
		return Cocoa::CreateUnique<StubTexture2D>();
	}

	void StubGraphicsDevice::DrawIndexed(const Cocoa::Graphics::VertexArray& vertexArray, uint32_t indexCount)
	{

	}
}
