#pragma once

#include <graphics/Shader.hpp>

namespace cocoa_tests::stubs
{
	class StubShader : public cocoa::graphics::Shader
	{
	public:
		StubShader() = default;
		~StubShader() override = default;
		void bind() const override;
		void unbind() const override;
		void setInt(const std::string& name, int value) const override;
		void setFloat(const std::string& name, float value) const override;
		void setVector4(const std::string& name, const cocoa::math::Vector4f& value) const override;
		void setMatrix4(const std::string& name, const cocoa::math::Matrix4f& value) const override;
		void setIntArray(const std::string& name, const int* values, int count) const override;
		void setVector2fArray(const std::string &name, const cocoa::math::Vector2f *values, int count) const override;
	};
}
