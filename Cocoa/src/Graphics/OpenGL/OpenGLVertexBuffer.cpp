#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"

#include <GL/glew.h>

namespace Cocoa::Graphics
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, uint32_t size)
		: m_vbo(0)
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
		if (m_vbo == 0)
			return;

		GLuint vbo = static_cast<GLuint>(m_vbo);
		glDeleteBuffers(1, &vbo);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(m_vbo));
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}