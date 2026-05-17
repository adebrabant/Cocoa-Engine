#include "Platforms/GLFW/GLFWWindow.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace VexEngine::Platforms
{
	GLFWWindow::GLFWWindow() :
		m_window(nullptr),
		m_title(),
		m_width(0),
		m_height(0)
	{

	}

	GLFWWindow::~GLFWWindow()
	{
		Shutdown();
	}

	void GLFWWindow::OnInit(const WindowProperties& properties)
	{
		if (m_window)
			throw std::logic_error("GLFWWindow is already initialized.");

		m_width = properties.GetWidth();
		m_height = properties.GetHeight();
		m_title = properties.GetTitle();

		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(
			m_width, 
			m_height, 
			m_title.c_str(), 
			nullptr, 
			nullptr);

		if (!m_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window.");
		}

		CenterWindow();

		glfwMakeContextCurrent(m_window);
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