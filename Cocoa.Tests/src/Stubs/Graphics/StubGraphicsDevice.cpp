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
#include <Core/Memory.hpp>

namespace Cocoa::Stubs
{
	void StubGraphicsDevice::BeginFrame()
	{

	}

	void StubGraphicsDevice::EndFrame()
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

	Unique<Graphics::Shader> StubGraphicsDevice::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		return CreateUnique<StubShader>();
	}

	Unique<Graphics::VertexArray> StubGraphicsDevice::CreateVertexArray()
	{
		return CreateUnique<StubVertexArray>();
	}

	Unique<Graphics::VertexBuffer> StubGraphicsDevice::CreateVertexBuffer(uint32_t size, const Graphics::BufferLayout& bufferLayout)
	{
		return CreateUnique<StubVertexBuffer>(size, bufferLayout);
	}

	Unique<Graphics::VertexBuffer> StubGraphicsDevice::CreateVertexBuffer(const void* vertices, uint32_t size, const Graphics::BufferLayout& bufferLayout)
	{
		return CreateUnique<StubVertexBuffer>(vertices, size, bufferLayout);
	}

	Unique<Graphics::IndexBuffer> StubGraphicsDevice::CreateIndexBuffer(const uint32_t* indices, uint32_t count)
	{
		return CreateUnique<StubIndexBuffer>(indices, count);
	}

	Unique<Graphics::Texture2D> StubGraphicsDevice::CreateTexture2D(Graphics::TextureSpec textureSpec, const unsigned char* pixels)
	{
		return CreateUnique<StubTexture2D>();
	}

	void StubGraphicsDevice::DrawIndexed(const Graphics::VertexArray& vertexArray, uint32_t indexCount)
	{

	}
}
