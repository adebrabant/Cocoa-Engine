#include "graphics/BufferLayout.hpp"
#include "graphics/BufferElement.hpp"

namespace cocoa::graphics
{
	BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) :
		m_elements(elements)
	{
        uint32_t offset = 0;

        for (auto& element : m_elements)
        {
            element.offset = element.offset > 0 ? element.offset : offset;
            offset = element.offset + element.size;
            m_stride = offset;
        }
	}
}
