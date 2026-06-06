#include "Graphics/OpenGL/OpenGLShader.hpp"

#include <GL/glew.h>
#include <iostream>

namespace Cocoa::Graphics
{
	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
		: m_rendererId(0)
	{
		const char* vertexShaderCStr = vertexSource.c_str();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
		glCompileShader(vertexShader);

		GLint vertexCompileSuccess = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompileSuccess);

		if (!vertexCompileSuccess)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			std::cerr << "Vertex shader comp failed: " << infoLog << std::endl;
		}

		const char* fragmentShaderCStr = fragmentSource.c_str();
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderCStr, nullptr);
		glCompileShader(fragmentShader);

		GLint fragmentCompileSuccess = 0;
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
		m_rendererId = static_cast<uint32_t>(shaderProgram);
	}

	OpenGLShader::~OpenGLShader()
	{
		Destroy();
	}

	OpenGLShader::OpenGLShader(OpenGLShader&& other) noexcept :
		m_rendererId(other.m_rendererId)
	{
		other.m_rendererId = 0;
	}

	OpenGLShader& OpenGLShader::operator==(OpenGLShader&& other) noexcept
	{
		if (this == &other)
			return *this;

		Destroy();
		m_rendererId = other.m_rendererId;
		other.m_rendererId = 0;

		return *this;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(static_cast<GLuint>(m_rendererId));
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(
			static_cast<GLuint>(m_rendererId),
			name.c_str()
		);

		glUniform1i(location, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(
			static_cast<GLuint>(m_rendererId),
			name.c_str()
		);

		glUniform1f(location, value);
	}

	void OpenGLShader::Destroy() const
	{
		if (m_rendererId <= 0)
			return;

		glDeleteProgram(static_cast<GLuint>(m_rendererId));
	}
}