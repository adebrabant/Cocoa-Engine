#include "Graphics/OpenGL/OpenGLVertexArray.hpp"
#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"
#include "Graphics/OpenGL/OpenGLIndexBuffer.hpp"

#include <GL/glew.h>

namespace Cocoa::Graphics
{
	OpenGLVertexArray::OpenGLVertexArray() 
		: m_vao(0)
	{
		GLuint vertexArray = 0;
		glGenVertexArrays(1, &vertexArray);
		m_vao = static_cast<uint32_t>(vertexArray);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		if (m_vao == 0)
			return;

		GLuint vertexArray = static_cast<GLuint>(m_vao);
		glDeleteVertexArrays(1, &vertexArray);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(static_cast<GLuint>(m_vao));
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	// ToDo: Remove hardcoded values
	void OpenGLVertexArray::AddVertexBuffer(const OpenGLVertexBuffer& vertexBuffer)
	{
		Bind();
		vertexBuffer.Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			2,
			GL_FLOAT,
			GL_FALSE,
			4 * sizeof(float),
			nullptr
		);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			4 * sizeof(float),
			reinterpret_cast<const void*>(2 * sizeof(float))
		);

		vertexBuffer.Unbind();
		Unbind();
	}

	void OpenGLVertexArray::SetIndexBuffer(const OpenGLIndexBuffer& indexBuffer)
	{
		Bind();
		indexBuffer.Bind();
		Unbind();
	}
}