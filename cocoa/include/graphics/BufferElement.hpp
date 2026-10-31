#pragma once

#include <string>
#include <stdexcept>

namespace cocoa::graphics
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		UInt,
		Bool
	};

	struct BufferElement
	{
		uint32_t location;
		ShaderDataType shaderDataType;
		std::string name;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement(
			uint32_t shaderLocation,
			ShaderDataType shaderType,
			const std::string& name,
			uint32_t offset = 0,
			bool normalized = false
		) :
			location(shaderLocation),
			shaderDataType(shaderType),
			name(name),
			size(shaderDataTypeSize(shaderType)),
			offset(offset),
			normalized(normalized)
		{

		}

		[[nodiscard]] bool isInteger() const
		{
			switch (shaderDataType)
			{
			case ShaderDataType::Int:  return true;
			case ShaderDataType::Int2: return true;
			case ShaderDataType::Int3: return true;
			case ShaderDataType::Int4: return true;
			case ShaderDataType::UInt: return true;
			default: return false;
			}
		}

		[[nodiscard]] uint32_t getScalarCount() const
		{
			switch (shaderDataType)
			{
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;

			case ShaderDataType::Int:    return 1;
			case ShaderDataType::Int2:   return 2;
			case ShaderDataType::Int3:   return 3;
			case ShaderDataType::Int4:   return 4;

			case ShaderDataType::UInt:   return 1;

			case ShaderDataType::Bool:   return 1;

			default:
				throw std::runtime_error("Unknown ShaderDataType.");
			}
		}

	private:
		static uint32_t shaderDataTypeSize(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:  return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;

			case ShaderDataType::Int:    return 4;
			case ShaderDataType::Int2:   return 4 * 2;
			case ShaderDataType::Int3:   return 4 * 3;
			case ShaderDataType::Int4:   return 4 * 4;

			case ShaderDataType::UInt:   return 4;

			case ShaderDataType::Bool:   return 1;

			default:
				throw std::runtime_error("Unknown ShaderDataType.");
			}
		}
	};
}
