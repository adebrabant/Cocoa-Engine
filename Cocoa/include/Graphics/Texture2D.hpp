#pragma once

#include <cstdint>

namespace Cocoa::Graphics
{
	class Texture2D
	{
	public:
		virtual ~Texture2D() = default;
		virtual void Bind(uint32_t slot) const = 0;
		[[nodiscard]] virtual uint32_t GetWidth() const = 0;
		[[nodiscard]] virtual uint32_t GetHeight() const = 0;
	};
}