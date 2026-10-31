#pragma once

#include "graphics/IndexBuffer.hpp"
#include <cstdint>

namespace cocoa::graphics
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		OpenGLIndexBuffer(const OpenGLIndexBuffer&) = delete;
		OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&) = delete;

		OpenGLIndexBuffer(OpenGLIndexBuffer&& other) noexcept;
		OpenGLIndexBuffer& operator=(OpenGLIndexBuffer&& other) noexcept;

		void bind() const override;
		void unbind() const override;
		[[nodiscard]] uint32_t getCount() const override;

	private:
		void Destroy() const;

	private:
		uint32_t m_ibo;
		uint32_t m_count;
	};
}
