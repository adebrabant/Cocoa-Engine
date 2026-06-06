#pragma once

#include <cstdint>

namespace Cocoa::Graphics
{
	class Texture2D
	{
	public:
		virtual ~Texture2D() = default;
		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
	};
}