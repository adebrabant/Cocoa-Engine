#include "graphics/opengl/OpenGLGraphicsDevice.hpp"
#include "graphics/BufferElement.hpp"
#include "graphics/BufferLayout.hpp"
#include "graphics/TextureSpec.hpp"
#include "graphics/opengl/OpenGLFramebuffer.hpp"
#include "graphics/opengl/OpenGLIndexBuffer.hpp"
#include "graphics/opengl/OpenGLShader.hpp"
#include "graphics/opengl/OpenGLTexture2D.hpp"
#include "graphics/opengl/OpenGLVertexArray.hpp"
#include "graphics/opengl/OpenGLVertexBuffer.hpp"

#include <GL/glew.h>

namespace cocoa::graphics
{
	OpenGLGraphicsDevice::OpenGLGraphicsDevice() :
		m_viewport(0, 0, 10, 10)
	{

	}

	OpenGLGraphicsDevice::~OpenGLGraphicsDevice() = default;

	void OpenGLGraphicsDevice::beginFrame()
	{
		// ToDo: Reserved for per-frame graphics device setup
	}

	void OpenGLGraphicsDevice::endFrame()
	{
		// ToDo: Reserved for per-frame graphics device cleanup/submission
	}

	void OpenGLGraphicsDevice::setBlendMode(const BlendMode mode)
	{
		switch (mode)
		{
		case BlendMode::Opaque:
			glDisable(GL_BLEND);
			break;
		case BlendMode::Alpha:
			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case BlendMode::Additive:
			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case BlendMode::Subtractive:
			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_SUBTRACT);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case BlendMode::ReverseSubtract:
			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		}
	}

	void OpenGLGraphicsDevice::setViewport(
		const int32_t x,
		const int32_t y,
		const uint32_t width,
		const uint32_t height)
	{
		glViewport(
			x,
			y,
			static_cast<GLsizei>(width),
			static_cast<GLsizei>(height)
		);

		m_viewport.resize(x, y, width, height);
	}

	void OpenGLGraphicsDevice::setClearColor(const float red, const float green, const float blue, const float alpha)
	{
		glClearColor(
			red,
			green,
			blue,
			alpha
		);
	}

	void OpenGLGraphicsDevice::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	Unique<Shader> OpenGLGraphicsDevice::createShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		return createUnique<OpenGLShader>(vertexSource, fragmentSource);
	}

	Unique<VertexArray> OpenGLGraphicsDevice::createVertexArray()
	{
		return createUnique<OpenGLVertexArray>();
	}

	Unique<VertexBuffer> OpenGLGraphicsDevice::createVertexBuffer(uint32_t size, const BufferLayout& bufferLayout)
	{
		return createUnique<OpenGLVertexBuffer>(size, bufferLayout);
	}

	Unique<VertexBuffer> OpenGLGraphicsDevice::createVertexBuffer(const void* vertices, uint32_t size, const BufferLayout& bufferLayout)
	{
		return createUnique<OpenGLVertexBuffer>(vertices, size, bufferLayout);
	}

	Unique<IndexBuffer> OpenGLGraphicsDevice::createIndexBuffer(const uint32_t* indices, uint32_t count)
	{
		return createUnique<OpenGLIndexBuffer>(indices, count);
	}

	Unique<Texture2D> OpenGLGraphicsDevice::createTexture2D(TextureSpec textureSpec, const unsigned char* pixels)
	{
		return createUnique<OpenGLTexture2D>(textureSpec, pixels);
	}

	Unique<Framebuffer> OpenGLGraphicsDevice::createFramebuffer(const FramebufferSpec& framebufferSpec)
	{
		return createUnique<OpenGLFramebuffer>(framebufferSpec);
	}

	void OpenGLGraphicsDevice::drawIndexed(const VertexArray& vertexArray, uint32_t indexCount)
	{
		vertexArray.bind();

		glDrawElements(
			GL_TRIANGLES,
			static_cast<GLsizei>(indexCount),
			GL_UNSIGNED_INT,
			nullptr
		);

		vertexArray.unbind();
	}
}
