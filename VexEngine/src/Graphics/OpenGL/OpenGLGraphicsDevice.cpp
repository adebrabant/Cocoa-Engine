#include "Graphics/OpenGL/OpenGLGraphicsDevice.hpp"

#include <GL/glew.h>

namespace VexEngine::Graphics
{
	void OpenGLGraphicsDevice::SetViewport(uint32_t width, uint32_t height)
	{
		glViewport(
			0,
			0,
			static_cast<GLsizei>(width),
			static_cast<GLsizei>(height)
		);
	}

	void OpenGLGraphicsDevice::SetClearColor(float red, float green, float blue, float alpha)
	{
		glClearColor(
			red,
			green,
			blue,
			alpha
		);
	}

	void OpenGLGraphicsDevice::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
}