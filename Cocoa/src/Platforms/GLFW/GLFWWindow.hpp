#pragma once

#include "Platforms/Window.hpp"
#include "Platforms/WindowProperties.hpp"

struct GLFWwindow;

namespace Cocoa::Events
{
	class EventBus;
}

namespace Cocoa::Platforms
{
	class GLFWWindow : public Window
	{
	public:
		GLFWWindow(const Cocoa::Events::EventBus& eventBus,const WindowProperties& properties);
		~GLFWWindow() override;

		GLFWWindow(const GLFWWindow&) = delete;
		GLFWWindow& operator = (const GLFWWindow&) = delete;

		void OnUpdate() override;
		[[nodiscard]] bool IsOpen() const override;
		[[nodiscard]] uint32_t GetWidth() const override;
		[[nodiscard]] uint32_t GetHeight() const override;
		[[nodiscard]] void* GetNative() const override;

	private:
		static void FrameBufferSizeCallback(
			GLFWwindow* window,
			int width,
			int height);
		void CenterWindow() const;
		void Shutdown();

	private:
		const Events::EventBus& m_eventBus;
		GLFWwindow* m_window = nullptr;
		std::string m_title;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
	};
}