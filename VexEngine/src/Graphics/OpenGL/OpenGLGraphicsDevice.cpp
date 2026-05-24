#include "Graphics/OpenGL/OpenGLGraphicsDevice.hpp"

#include <GL/glew.h>
#include <iostream>

namespace VexEngine::Graphics
{
	void OpenGLGraphicsDevice::BeginFrame()
	{
		// ToDo: Reserved for per-frame graphics device setup
	}

	void OpenGLGraphicsDevice::EndFrame()
	{
		// ToDo: Reserved for per-frame graphics device cleanup/submission
	}

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

	void OpenGLGraphicsDevice::RenderTempTriangle()
	{
		if (!m_isTempTriangleInit)
		{
			InitTempTriangle();
			m_isTempTriangleInit = true;
		}

		glUseProgram(static_cast<GLuint>(m_tempTriangleShaderProgram));
		glBindVertexArray(static_cast<GLuint>(m_tempTriangleVertexArray));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void OpenGLGraphicsDevice::InitTempTriangle()
	{
		const char* vertexShaderSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			
			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		const char* fragmentShaderSource = R"(
			#version 330 core
			
			out vec4 FragColor;
			
			void main()
			{
				FragColor = vec4(1.0, 0.4, 0.2, 1.0);
			}
		)";

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		GLint vertexCompileSuccess;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompileSuccess);

		if (!vertexCompileSuccess)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			std::cerr << "Vertex shader comp failed: " << infoLog << std::endl;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);

		GLint fragmentCompileSuccess = false;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentCompileSuccess);

		if (!fragmentCompileSuccess)
		{
			char infoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			std::cerr << "Fragment shader comp failed: " << infoLog << std::endl;
		}

		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		GLint linkSuccess = 0;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);

		if (!linkSuccess)
		{
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
			std::cerr << "Shader program link failed: " << infoLog << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		GLuint vertexArray = 0;
		GLuint vertexBuffer = 0;

		glGenVertexArrays(1, &vertexArray);
		glGenBuffers(1, &vertexBuffer);

		glBindVertexArray(vertexArray);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(vertices),
			vertices,
			GL_STATIC_DRAW
		);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0, 
			3,
			GL_FLOAT,
			GL_FALSE,
			3 * sizeof(float),
			nullptr
		);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_tempTriangleShaderProgram = shaderProgram;
		m_tempTriangleVertexArray = vertexArray;
		m_tempTriangleVertexBuffer = vertexBuffer;
	}
}