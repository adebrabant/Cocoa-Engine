#pragma once

#include <cstdint>

namespace cocoa::Graphics
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		[[nodiscard]] virtual uint32_t GetCount() const = 0;
	};
}