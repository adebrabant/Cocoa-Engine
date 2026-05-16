#pragma once
#include "Platforms/WindowProperties.hpp"

#include <cstdint>

namespace VexEngine::Platforms
{
	class IWindow
	{
	public:
		virtual ~IWindow() = default;
		virtual void OnInit(const WindowProperties& properties) = 0;
		virtual void OnUpdate() = 0;
		virtual bool IsOpen() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void* GetNative() const = 0;
	};
}