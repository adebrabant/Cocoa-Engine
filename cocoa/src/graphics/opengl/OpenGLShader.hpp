#pragma once

#include "graphics/Shader.hpp"

namespace cocoa::graphics
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
		void SetVector4(const std::string& name, const math::Vector4f& value) const override;
		void SetMatrix4(const std::string& name, const math::Matrix4f& value) const override;
		void SetIntArray(const std::string& name, const int* values, int count) const override;
		void SetVector2fArray(const std::string& name, const math::Vector2f* values, int count) const override;

	private:
		void Destroy() const;

	private:
		uint32_t m_rendererId;
	};
}
