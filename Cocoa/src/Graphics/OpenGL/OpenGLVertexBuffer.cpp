#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"
#include "Graphics/BufferLayout.hpp"

#include <GL/glew.h>
#include <utility>

namespace Cocoa::Graphics
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, uint32_t size, const BufferLayout& bufferLayout) : 
		m_bufferLayout(bufferLayout),
		m_vbo(0)
	{
		GLuint vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			size,
			vertices,
			GL_STATIC_DRAW
		);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_vbo = static_cast<uint32_t>(vbo);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		Destroy();
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(OpenGLVertexBuffer&& other) noexcept : 
		m_bufferLayout(std::move(other.m_bufferLayout)),
		m_vbo(other.m_vbo)
	{
		other.m_vbo = 0;
	}

	OpenGLVertexBuffer& OpenGLVertexBuffer::operator=(OpenGLVertexBuffer&& other) noexcept
	{
		if (this == &other)
			return *this;

		Destroy();
		m_bufferLayout = std::move(other.m_bufferLayout);
		m_vbo = other.m_vbo;
		other.m_vbo = 0;

		return *this;
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(m_vbo));
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::Destroy()
	{
		if (m_vbo <= 0)
			return;

		GLuint vbo = static_cast<GLuint>(m_vbo);
		glDeleteBuffers(1, &vbo);
		m_vbo = 0;
	}
}