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

		void bind() const override;
		void unbind() const override;

		void setInt(const std::string& name, int value) const override;
		void setFloat(const std::string& name, float value) const override;
		void setVector4(const std::string& name, const math::Vector4f& value) const override;
		void setMatrix4(const std::string& name, const math::Matrix4f& value) const override;
		void setIntArray(const std::string& name, const int* values, int count) const override;
		void setVector2fArray(const std::string& name, const math::Vector2f* values, int count) const override;

	private:
		void Destroy() const;

	private:
		uint32_t m_rendererId;
	};
}
