#pragma once

#include <cstdint>

namespace cocoa::platforms
{
	class Window
	{
	public:
		virtual ~Window() = default;
		virtual void processEvents() = 0;
		virtual void waitForEvents(float duration) const = 0;
		virtual void onUpdate() = 0;
		[[nodiscard]] virtual bool isOpen() const = 0;
		[[nodiscard]] virtual uint32_t getWidth() const = 0;
		[[nodiscard]] virtual uint32_t getHeight() const = 0;
		[[nodiscard]] virtual void* getNative() const = 0;
	};
}
