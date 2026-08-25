#include "Stubs/Graphics/StubVertexBuffer.hpp"

namespace Cocoa::Stubs
{
    StubVertexBuffer::StubVertexBuffer(uint32_t size, const Graphics::BufferLayout &bufferLayout) :
        m_bufferLayout(bufferLayout)
    {

    }

    StubVertexBuffer::StubVertexBuffer(const void *vertices, uint32_t size, const Graphics::BufferLayout &bufferLayout) :
        m_bufferLayout(bufferLayout)
    {

    }

    StubVertexBuffer::~StubVertexBuffer() = default;

    void StubVertexBuffer::Bind() const
    {

    }

    void StubVertexBuffer::Unbind() const
    {

    }

    void StubVertexBuffer::SetData(const void *data, uint32_t size) const
    {

    }

    const Graphics::BufferLayout& StubVertexBuffer::GetLayout() const
    {
        return m_bufferLayout;
    }
}
