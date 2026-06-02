#pragma once

#include "Graphics/BufferElement.hpp"
#include <vector>
#include <cstdint>
#include <initializer_list>

namespace Cocoa::Graphics
{
	class BufferLayout
	{
	public:
		BufferLayout(std::initializer_list<BufferElement> elements);
		~BufferLayout() = default;

		uint32_t GetStride() const { return m_stride; }
		const std::vector<BufferElement>& GetElements() const { return m_elements; }

	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride;
	};
}