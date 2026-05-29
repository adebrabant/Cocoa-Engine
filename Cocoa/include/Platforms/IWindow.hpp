#pragma once

#include <cstdint>

namespace Cocoa::Platforms
{
	class IWindow
	{
	public:
		virtual ~IWindow() = default;
		virtual void OnUpdate() = 0;
		virtual bool IsOpen() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void* GetNative() const = 0;
	};
}