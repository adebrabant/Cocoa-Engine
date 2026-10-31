#include "graphics/opengl/OpenGLContext.hpp"

#include <GL/glew.h>
#include <iostream>
#include <stdexcept>

namespace cocoa::graphics
{
	OpenGLContext::OpenGLContext()
	{
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
			throw std::runtime_error("failed to initialize GLEW");

		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	}
}
