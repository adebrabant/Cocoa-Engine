#pragma once

#include <cstdint>

namespace cocoa::graphics
{
	class BufferLayout;

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void setData(const void* data, uint32_t size) const = 0;
		[[nodiscard]] virtual const BufferLayout& getLayout() const = 0;
	};
}
