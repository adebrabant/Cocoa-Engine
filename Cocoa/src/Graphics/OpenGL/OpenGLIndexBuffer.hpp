#pragma once

#include "Graphics/IndexBuffer.hpp"
#include <cstdint>

namespace Cocoa::Graphics
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

		void Bind() const override;
		void Unbind() const override;
		uint32_t GetCount() const override;

	private:
		void Destroy() const;

	private:
		uint32_t m_ibo;
		uint32_t m_count;
	};
}