#include "Graphics/OpenGL/OpenGLIndexBuffer.hpp"

#include <GL/glew.h>

namespace Cocoa::Graphics
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t count) : 
		m_ibo(0),
		m_count(count)
	{
		GLuint indexBuffer = 0;
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			count * sizeof(uint32_t),
			indices,
			GL_STATIC_DRAW
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		m_ibo = static_cast<uint32_t>(indexBuffer);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		if (m_ibo == 0)
			return;

		GLuint indexBuffer = static_cast<GLuint>(m_ibo);
		glDeleteBuffers(1, &indexBuffer);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(m_ibo));
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const
	{
		return m_count;
	}
}