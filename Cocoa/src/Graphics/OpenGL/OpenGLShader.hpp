#pragma once

#include <cstdint>
#include <string>

namespace Cocoa::Graphics
{
	class OpenGLShader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		OpenGLShader(const OpenGLShader&) = delete;
		OpenGLShader& operator=(const OpenGLShader&) = delete;

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;

		// ToDo: Add once engine math types exist.
		// void SetMat4(const std::string& name, const Matrix4& value);

	private:
		uint32_t m_rendererId;
	};
}