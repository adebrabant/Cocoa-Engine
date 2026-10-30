#pragma once

#include <graphics/Shader.hpp>

namespace CocoaTests::Stubs
{
	class StubShader : public cocoa::Graphics::Shader
	{
	public:
		StubShader() = default;
		~StubShader() override = default;
		void Bind() const override;
		void Unbind() const override;
		void SetInt(const std::string& name, int value) const override;
		void SetFloat(const std::string& name, float value) const override;
		void SetVector4(const std::string& name, const cocoa::Math::Vector4f& value) const override;
		void SetMatrix4(const std::string& name, const cocoa::Math::Matrix4f& value) const override;
		void SetIntArray(const std::string& name, const int* values, int count) const override;
		void SetVector2fArray(const std::string &name, const cocoa::Math::Vector2f *values, int count) const override;
	};
}