#pragma once

#include <cstdint>
#include <string>

namespace cocoa::math
{
	struct Vector2f;
	struct Vector4f;
	struct Matrix4f;
}

namespace cocoa::graphics
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetInt(const std::string& name, int value) const = 0;
		virtual void SetFloat(const std::string& name, float value) const = 0;
		virtual void SetVector4(const std::string& name, const math::Vector4f& value) const = 0;
		virtual void SetMatrix4(const std::string& name, const math::Matrix4f& value) const = 0;
		virtual void SetIntArray(const std::string& name, const int* values, int count) const = 0;
		virtual void SetVector2fArray(const std::string& name, const math::Vector2f* values, int count) const = 0;
	};
}
