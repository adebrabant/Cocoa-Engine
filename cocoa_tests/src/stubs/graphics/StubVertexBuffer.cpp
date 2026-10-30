#include "stubs/Graphics/StubVertexBuffer.hpp"

namespace CocoaTests::Stubs
{
    StubVertexBuffer::StubVertexBuffer(uint32_t size, const cocoa::Graphics::BufferLayout &bufferLayout, VertexBufferCapture& vertexBufferCapture) :
        m_bufferLayout(bufferLayout),
        m_vertexBufferCapture(vertexBufferCapture)
    {

    }

    StubVertexBuffer::StubVertexBuffer(const void *vertices, uint32_t size, const cocoa::Graphics::BufferLayout &bufferLayout, VertexBufferCapture& vertexBufferCapture) :
        m_bufferLayout(bufferLayout),
        m_vertexBufferCapture(vertexBufferCapture)
    {

    }

    StubVertexBuffer::~StubVertexBuffer() = default;

    void StubVertexBuffer::Bind() const
    {

    }

    void StubVertexBuffer::Unbind() const
    {

    }

    void StubVertexBuffer::SetData(const void* data, uint32_t size) const
    {
        const auto* bytes = static_cast<const std::byte*>(data);
        m_vertexBufferCapture.Data.assign(bytes, bytes + size);
        m_vertexBufferCapture.Stride = m_bufferLayout.GetStride();
    }

    const cocoa::Graphics::BufferLayout& StubVertexBuffer::GetLayout() const
    {
        return m_bufferLayout;
    }
}
