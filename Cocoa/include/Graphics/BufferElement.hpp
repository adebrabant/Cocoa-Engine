#pragma once

#include <string>
#include <stdexcept>

namespace Cocoa::Graphics
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
		uint32_t Location;
		ShaderDataType Type;
		std::string Name;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement(
			uint32_t shaderLocation,
			ShaderDataType shaderType, 
			const std::string& name, 
			uint32_t offset = 0, 
			bool normalized = false
		) :
			Location(shaderLocation),
			Type(shaderType),
			Name(name),
			Size(ShaderDataTypeSize(shaderType)),
			Offset(offset),
			Normalized(normalized)
		{

		}

		[[nodiscard]] bool IsInteger() const
		{
			switch (Type)
			{
			case ShaderDataType::Int:  return true;
			case ShaderDataType::Int2: return true;
			case ShaderDataType::Int3: return true;
			case ShaderDataType::Int4: return true;
			case ShaderDataType::UInt: return true;
			default: return false;
			}
		}

		[[nodiscard]] uint32_t GetScalarCount() const
		{
			switch (Type)
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
		static uint32_t ShaderDataTypeSize(ShaderDataType type)
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