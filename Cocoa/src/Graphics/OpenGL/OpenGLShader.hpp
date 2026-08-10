#pragma once

#include "Graphics/Shader.hpp"
#include <cstdint>
#include <string>

namespace Cocoa::Graphics
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader() override;

		OpenGLShader(const OpenGLShader&) = delete;
		OpenGLShader& operator=(const OpenGLShader&) = delete;

		OpenGLShader(OpenGLShader&& other) noexcept;
		OpenGLShader& operator==(OpenGLShader&& other) noexcept;

		void Bind() const override;
		void Unbind() const override;

		void SetInt(const std::string& name, int value) const override;
		void SetFloat(const std::string& name, float value) const override;
		void SetVector4(const std::string& name, const Math::Vector4f& value) const override;
		void SetMatrix4(const std::string& name, const Math::Matrix4f& value) const override;

	private:
		void Destroy() const;

	private:
		uint32_t m_rendererId;
	};
}