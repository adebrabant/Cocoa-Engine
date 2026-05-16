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

		glfwMakeContextCurrent(m_window);
	}

	void GLFWWindow::OnUpdate()
	{
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

	void GLFWWindow::Shutdown()
	{
		if (!m_window)
			return;

		glfwDestroyWindow(m_window);
		glfwTerminate();
		m_window = nullptr;
	}
}