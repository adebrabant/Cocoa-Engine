#pragma once

#include <string>

namespace Cocoa::Math
{
	struct Vector4f;
}

namespace Cocoa::Graphics
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetInt(const std::string& name, int value) const = 0;
		virtual void SetFloat(const std::string& name, float value) const = 0;
		virtual void SetVector4(const std::string& name, const Math::Vector4f& value) const = 0;
	};
}