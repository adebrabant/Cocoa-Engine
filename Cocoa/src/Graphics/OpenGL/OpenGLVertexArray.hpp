#pragma once
#include <cstdint>

namespace Cocoa::Graphics
{
	class OpenGLVertexBuffer;
	class OpenGLIndexBuffer;

	class OpenGLVertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		OpenGLVertexArray(const OpenGLVertexArray&) = delete;
		OpenGLVertexArray& operator=(const OpenGLVertexArray&) = delete;

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const OpenGLVertexBuffer& vertexBuffer);
		void SetIndexBuffer(const OpenGLIndexBuffer& indexBuffer);

	private:
		uint32_t m_vao;
	};
}