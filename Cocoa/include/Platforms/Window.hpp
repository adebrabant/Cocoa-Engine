#pragma once

#include <cstdint>

namespace Cocoa::Platforms
{
	class Window
	{
	public:
		virtual ~Window() = default;
		virtual void ProcessEvents() = 0;
		virtual void WaitForEvents(float duration) const = 0;
		virtual void OnUpdate() = 0;
		[[nodiscard]] virtual bool IsOpen() const = 0;
		[[nodiscard]] virtual uint32_t GetWidth() const = 0;
		[[nodiscard]] virtual uint32_t GetHeight() const = 0;
		[[nodiscard]] virtual void* GetNative() const = 0;
	};
}