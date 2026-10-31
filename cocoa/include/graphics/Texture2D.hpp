#pragma once

#include <cstdint>

namespace cocoa::graphics
{
	class Texture2D
	{
	public:
		virtual ~Texture2D() = default;
		virtual void bind(uint32_t slot) const = 0;
		[[nodiscard]] virtual uint32_t getWidth() const = 0;
		[[nodiscard]] virtual uint32_t getHeight() const = 0;
	};
}
