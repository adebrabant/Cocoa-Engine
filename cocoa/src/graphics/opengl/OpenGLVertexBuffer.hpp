#pragma once

#include "graphics/BufferLayout.hpp"
#include "graphics/VertexBuffer.hpp"

#include <cstdint>

namespace cocoa::graphics
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size, const BufferLayout& bufferLayout);
		OpenGLVertexBuffer(const void* vertices, uint32_t size, const BufferLayout& bufferLayout);
		~OpenGLVertexBuffer() override;

		OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;
		OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;

		OpenGLVertexBuffer(OpenGLVertexBuffer&& other) noexcept;
		OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&& other) noexcept;

		void bind() const override;
		void unbind() const override;
		void setData(const void* data, uint32_t size) const override;

		[[nodiscard]] const BufferLayout& getLayout() const override { return m_bufferLayout; }

	private:
		void Destroy();

	private:
		BufferLayout m_bufferLayout;
		uint32_t m_vbo;
	};
}
