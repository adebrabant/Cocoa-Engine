#pragma once

#include <cstdint>

namespace Cocoa::Graphics
{
	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer(const float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;
		OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_vbo;
	};
}