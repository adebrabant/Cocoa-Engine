#include "Platforms/GLFW/GLFWWindow.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Cocoa::Platforms
{
	GLFWWindow::GLFWWindow(const WindowProperties& properties) :
		m_window(nullptr),
		m_title(properties.GetTitle()),
		m_width(properties.GetWidth()),
		m_height(properties.GetHeight())
	{
		if (m_window)
			throw std::logic_error("GLFWWindow is already initialized.");

		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(
			static_cast<int>(m_width),
			static_cast<int>(m_height),
			m_title.c_str(),
			nullptr,
			nullptr
		);

		if (!m_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window.");
		}

		CenterWindow();

		glfwMakeContextCurrent(m_window);
	}

	GLFWWindow::~GLFWWindow()
	{
		Shutdown();
	}

	void GLFWWindow::OnUpdate()
	{
		if (!m_window)
			throw std::logic_error("GLFWWindow must be initialized before OnUpdate.");

		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	bool GLFWWindow::IsOpen() const
	{
		return m_window && !glfwWindowShouldClose(m_window);
	}

	uint32_t GLFWWindow::GetWidth() const
	{
		int width = 0;
		int height = 0;
		glfwGetWindowSize(m_window, &width, &height);
		return static_cast<uint32_t>(width);
	}

	uint32_t GLFWWindow::GetHeight() const
	{
		int width = 0;
		int height = 0;
		glfwGetWindowSize(m_window, &width, &height);
		return static_cast<uint32_t>(height);
	}

	void* GLFWWindow::GetNative() const
	{
		return m_window;
	}

	void GLFWWindow::CenterWindow()
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if (!monitor)
			return;

		const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
		if (!videoMode)
			return;

		int windowWidth = 0;
		int windowHeight = 0;
		glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

		const int x = (videoMode->width - windowWidth) / 2;
		const int y = (videoMode->height - windowWidth) / 2;

		glfwSetWindowPos(m_window, x, y);
	}

	void GLFWWindow::Shutdown()
	{
		if (!m_window)
			return;

		glfwDestroyWindow(m_window);
		glfwTerminate();
		m_window = nullptr;
	}
}