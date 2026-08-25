#include "Stubs/Graphics/StubIndexBuffer.hpp"

namespace Cocoa::Stubs
{
    StubIndexBuffer::StubIndexBuffer(const uint32_t *indices, uint32_t count) :
        m_count(count)
    {

    }

    StubIndexBuffer::~StubIndexBuffer() = default;

    void StubIndexBuffer::Bind() const
    {

    }

    void StubIndexBuffer::Unbind() const
    {

    }

    uint32_t StubIndexBuffer::GetCount() const
    {
        return m_count;
    }
}
