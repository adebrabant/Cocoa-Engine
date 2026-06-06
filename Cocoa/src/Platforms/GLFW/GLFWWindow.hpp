#pragma once

#include "Platforms/Window.hpp"
#include "Platforms/WindowProperties.hpp"

struct GLFWwindow;

namespace Cocoa::Platforms
{
	class GLFWWindow : public Window
	{
	public:
		GLFWWindow(const WindowProperties& properties);
		~GLFWWindow() override;

		GLFWWindow(const GLFWWindow&) = delete;
		GLFWWindow& operator = (const GLFWWindow&) = delete;

		void OnUpdate() override;
		bool IsOpen() const override;
		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		void* GetNative() const override;

	private:
		void CenterWindow();
		void Shutdown();

	private:
		GLFWwindow* m_window = nullptr;
		std::string m_title;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
	};
}