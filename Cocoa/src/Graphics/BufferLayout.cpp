#include "Graphics/BufferLayout.hpp"
#include "Graphics/BufferElement.hpp"

namespace Cocoa::Graphics
{
	BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) :
		m_elements(elements)
	{
        uint32_t offset = 0;

        for (auto& element : m_elements)
        {
            element.Offset = element.Offset > 0 ? element.Offset : offset;
            offset = element.Offset + element.Size;
            m_stride = offset;
        }
	}
}