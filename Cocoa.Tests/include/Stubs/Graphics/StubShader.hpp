#pragma once

#include <Graphics/Shader.hpp>

namespace Cocoa::Stubs
{
	class StubShader : public Graphics::Shader
	{
	public:
		StubShader() = default;
		~StubShader() override = default;
		void Bind() const override;
		void Unbind() const override;
		void SetInt(const std::string& name, int value) const override;
		void SetFloat(const std::string& name, float value) const override;
		void SetVector4(const std::string& name, const Math::Vector4f& value) const override;
		void SetMatrix4(const std::string& name, const Math::Matrix4f& value) const override;
	};
}