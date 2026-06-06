#include "Graphics/OpenGL/OpenGLVertexArray.hpp"
#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"
#include "Graphics/OpenGL/OpenGLIndexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/VertexBuffer.hpp"

#include <GL/glew.h>
#include <cstdint>
#include <stdexcept>

namespace Cocoa::Graphics
{
	static GLenum ToOpenGLScalarType(ShaderDataType shaderType)
	{
		switch (shaderType)
		{
		case Cocoa::Graphics::ShaderDataType::Float:
			return GL_FLOAT;
		case Cocoa::Graphics::ShaderDataType::Float2:
			return GL_FLOAT;
		case Cocoa::Graphics::ShaderDataType::Float3:
			return GL_FLOAT;
		case Cocoa::Graphics::ShaderDataType::Float4:
			return GL_FLOAT;
		case Cocoa::Graphics::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Cocoa::Graphics::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Cocoa::Graphics::ShaderDataType::Int:
			return GL_INT;
		case Cocoa::Graphics::ShaderDataType::Int2:
			return GL_INT;
		case Cocoa::Graphics::ShaderDataType::Int3:
			return GL_INT;
		case Cocoa::Graphics::ShaderDataType::Int4:
			return GL_INT;
		case Cocoa::Graphics::ShaderDataType::Bool:
			return GL_BOOL;
		default:
			throw std::runtime_error("Invalid Shader Type.");
		}
	}

	OpenGLVertexArray::OpenGLVertexArray() 
		: m_vao(0)
	{
		GLuint vertexArray = 0;
		glGenVertexArrays(1, &vertexArray);
		m_vao = static_cast<uint32_t>(vertexArray);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		Destroy();
	}

	OpenGLVertexArray::OpenGLVertexArray(OpenGLVertexArray&& other) noexcept :
		m_vao(other.m_vao)
	{
		other.m_vao = 0;
	}

	OpenGLVertexArray& OpenGLVertexArray::operator=(OpenGLVertexArray&& other) noexcept
	{
		if (this == &other)
			return *this;

		Destroy();
		m_vao = other.m_vao;
		other.m_vao = 0;

		return *this;
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(static_cast<GLuint>(m_vao));
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer)
	{
		Bind();
		vertexBuffer.Bind();

		for (const auto& element : vertexBuffer.GetLayout().GetElements())
		{
			glEnableVertexAttribArray(element.Location);
			glVertexAttribPointer(
				element.Location,
				static_cast<GLint>(element.GetScalarCount()),
				ToOpenGLScalarType(element.Type),
				element.Normalized != true ? GL_FALSE : GL_TRUE,
				vertexBuffer.GetLayout().GetStride(),
				reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset))
			);
		}

		vertexBuffer.Unbind();
		Unbind();
	}

	void OpenGLVertexArray::SetIndexBuffer(const IndexBuffer& indexBuffer)
	{
		Bind();
		indexBuffer.Bind();
		Unbind();
	}

	void OpenGLVertexArray::Destroy()
	{
		if (m_vao <= 0)
			return;

		GLuint vertexArray = static_cast<GLuint>(m_vao);
		glDeleteVertexArrays(1, &vertexArray);
	}
}