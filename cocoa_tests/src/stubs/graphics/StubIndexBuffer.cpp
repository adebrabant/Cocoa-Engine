#include "stubs/graphics/StubIndexBuffer.hpp"

namespace cocoa_tests::stubs
{
    StubIndexBuffer::StubIndexBuffer(const uint32_t *indices, uint32_t count) :
        m_count(count)
    {

    }

    StubIndexBuffer::~StubIndexBuffer() = default;

    void StubIndexBuffer::bind() const
    {

    }

    void StubIndexBuffer::unbind() const
    {

    }

    uint32_t StubIndexBuffer::getCount() const
    {
        return m_count;
    }
}
