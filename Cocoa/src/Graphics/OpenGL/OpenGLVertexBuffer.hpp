#pragma once

#include "Graphics/BufferLayout.hpp"

#include <cstdint>

namespace Cocoa::Graphics
{
	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer(const float* vertices, uint32_t size, const BufferLayout& bufferLayout);
		~OpenGLVertexBuffer();

		OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;
		OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;

		OpenGLVertexBuffer(OpenGLVertexBuffer&& other) noexcept;
		OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&& other) noexcept;

		void Bind() const;
		void Unbind() const;

		const BufferLayout& GetLayout() const { return m_bufferLayout; }

	private:
		void Destroy();

	private:
		BufferLayout m_bufferLayout;
		uint32_t m_vbo;
	};
}