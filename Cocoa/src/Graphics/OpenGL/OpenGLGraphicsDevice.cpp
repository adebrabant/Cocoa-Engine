#include "Graphics/OpenGL/OpenGLGraphicsDevice.hpp"
#include "Graphics/OpenGL/OpenGLShader.hpp"
#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"
#include "Graphics/OpenGL/OpenGLVertexArray.hpp"
#include "Graphics/OpenGL/OpenGLIndexBuffer.hpp"
#include "Graphics/OpenGL/OpenGLTexture2D.hpp"
#include "Graphics/TextureSpec.hpp"
#include "Graphics/BufferElement.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Core/Memory.hpp"

#include <GL/glew.h>
#include <iostream>

namespace Cocoa::Graphics
{
	OpenGLGraphicsDevice::OpenGLGraphicsDevice()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	OpenGLGraphicsDevice::~OpenGLGraphicsDevice()
	{

	}

	void OpenGLGraphicsDevice::BeginFrame()
	{
		// ToDo: Reserved for per-frame graphics device setup
	}

	void OpenGLGraphicsDevice::EndFrame()
	{
		// ToDo: Reserved for per-frame graphics device cleanup/submission
	}

	void OpenGLGraphicsDevice::SetViewport(uint32_t width, uint32_t height)
	{
		glViewport(
			0,
			0,
			static_cast<GLsizei>(width),
			static_cast<GLsizei>(height)
		);
	}

	void OpenGLGraphicsDevice::SetClearColor(float red, float green, float blue, float alpha)
	{
		glClearColor(
			red,
			green,
			blue,
			alpha
		);
	}

	void OpenGLGraphicsDevice::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	Unique<Shader> OpenGLGraphicsDevice::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		return CreateUnique<OpenGLShader>(vertexSource, fragmentSource);
	}

	Unique<VertexArray> OpenGLGraphicsDevice::CreateVertexArray()
	{
		return CreateUnique<OpenGLVertexArray>();
	}

	Unique<VertexBuffer> OpenGLGraphicsDevice::CreateVertexBuffer(const float* vertices, uint32_t size, const BufferLayout& bufferLayout)
	{
		return CreateUnique<OpenGLVertexBuffer>(vertices, size, bufferLayout);
	}

	Unique<IndexBuffer> OpenGLGraphicsDevice::CreateIndexBuffer(const uint32_t* indices, uint32_t count)
	{
		return CreateUnique<OpenGLIndexBuffer>(indices, count);
	}

	Unique<Texture2D> OpenGLGraphicsDevice::CreateTexture2D(TextureSpec textureSpec, const unsigned char* pixels)
	{
		return CreateUnique<OpenGLTexture2D>(textureSpec, pixels);
	}

	void OpenGLGraphicsDevice::DrawIndexed(const VertexArray& vertexArray, uint32_t indexCount)
	{
		vertexArray.Bind();

		glDrawElements(
			GL_TRIANGLES,
			static_cast<GLsizei>(indexCount),
			GL_UNSIGNED_INT,
			nullptr
		);

		vertexArray.Unbind();
	}
}