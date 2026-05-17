#pragma once

#include "Platforms/IWindow.hpp"

struct GLFWwindow;

namespace VexEngine::Platforms
{
	class GLFWWindow : public IWindow
	{
	public:
		GLFWWindow();
		~GLFWWindow() override;

		GLFWWindow(const GLFWWindow&) = delete;
		GLFWWindow& operator = (const GLFWWindow&) = delete;

		void OnInit(const WindowProperties& properties) override;
		void OnUpdate() override;
		bool IsOpen() const override;
		uint32_t GetWidth() const override { return m_width; }
		uint32_t GetHeight() const override { return m_height; }
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