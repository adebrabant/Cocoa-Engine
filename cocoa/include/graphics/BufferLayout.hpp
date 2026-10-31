#pragma once

#include "graphics/BufferElement.hpp"
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace cocoa::graphics
{
	class BufferLayout
	{
	public:
		BufferLayout(std::initializer_list<BufferElement> elements);
		~BufferLayout() = default;

		[[nodiscard]] uint32_t getStride() const { return m_stride; }
		[[nodiscard]] const std::vector<BufferElement>& getElements() const { return m_elements; }

	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride;
	};
}
