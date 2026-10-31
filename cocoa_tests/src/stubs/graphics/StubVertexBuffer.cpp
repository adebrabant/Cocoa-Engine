#include "stubs/graphics/StubVertexBuffer.hpp"

namespace cocoa_tests::stubs
{
    StubVertexBuffer::StubVertexBuffer(uint32_t size, const cocoa::graphics::BufferLayout &bufferLayout, VertexBufferCapture& vertexBufferCapture) :
        m_bufferLayout(bufferLayout),
        m_vertexBufferCapture(vertexBufferCapture)
    {

    }

    StubVertexBuffer::StubVertexBuffer(const void *vertices, uint32_t size, const cocoa::graphics::BufferLayout &bufferLayout, VertexBufferCapture& vertexBufferCapture) :
        m_bufferLayout(bufferLayout),
        m_vertexBufferCapture(vertexBufferCapture)
    {

    }

    StubVertexBuffer::~StubVertexBuffer() = default;

    void StubVertexBuffer::bind() const
    {

    }

    void StubVertexBuffer::unbind() const
    {

    }

    void StubVertexBuffer::setData(const void* data, uint32_t size) const
    {
        const auto* bytes = static_cast<const std::byte*>(data);
        m_vertexBufferCapture.Data.assign(bytes, bytes + size);
        m_vertexBufferCapture.Stride = m_bufferLayout.getStride();
    }

    const cocoa::graphics::BufferLayout& StubVertexBuffer::getLayout() const
    {
        return m_bufferLayout;
    }
}
