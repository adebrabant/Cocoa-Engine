#pragma once

#include "platforms/Window.hpp"
#include "platforms/WindowProperties.hpp"

struct GLFWwindow;

namespace cocoa::events
{
	class EventBus;
}

namespace cocoa::platforms
{
	class GLFWWindow : public Window
	{
	public:
		GLFWWindow(const cocoa::events::EventBus& eventBus,const WindowProperties& properties);
		~GLFWWindow() override;

		GLFWWindow(const GLFWWindow&) = delete;
		GLFWWindow& operator = (const GLFWWindow&) = delete;

		void onUpdate() override;
		void processEvents() override;
		void waitForEvents(float duration) const override;
		[[nodiscard]] bool isOpen() const override;
		[[nodiscard]] uint32_t getWidth() const override;
		[[nodiscard]] uint32_t getHeight() const override;
		[[nodiscard]] void* getNative() const override;

	private:
		static void FrameBufferSizeCallback(
			GLFWwindow* window,
			int width,
			int height);
		void CenterWindow() const;
		void Shutdown();

	private:
		const events::EventBus& m_eventBus;
		GLFWwindow* m_window = nullptr;
		std::string m_title;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
	};
}
