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
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void setInt(const std::string& name, int value) const = 0;
		virtual void setFloat(const std::string& name, float value) const = 0;
		virtual void setVector4(const std::string& name, const math::Vector4f& value) const = 0;
		virtual void setMatrix4(const std::string& name, const math::Matrix4f& value) const = 0;
		virtual void setIntArray(const std::string& name, const int* values, int count) const = 0;
		virtual void setVector2fArray(const std::string& name, const math::Vector2f* values, int count) const = 0;
	};
}
