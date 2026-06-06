#pragma once

#include "Graphics/BufferLayout.hpp"
#include "Graphics/VertexBuffer.hpp"

#include <cstdint>

namespace Cocoa::Graphics
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const float* vertices, uint32_t size, const BufferLayout& bufferLayout);
		~OpenGLVertexBuffer() override;

		OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;
		OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;

		OpenGLVertexBuffer(OpenGLVertexBuffer&& other) noexcept;
		OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&& other) noexcept;

		void Bind() const override;
		void Unbind() const override;

		const BufferLayout& GetLayout() const override { return m_bufferLayout; }

	private:
		void Destroy();

	private:
		BufferLayout m_bufferLayout;
		uint32_t m_vbo;
	};
}