#pragma once

#include <Graphics/VertexBuffer.hpp>
#include <Graphics/BufferLayout.hpp>

#include <vector>

namespace CocoaTests::Stubs
{
    struct VertexBufferCapture
    {
        std::vector<std::byte> Data;
        size_t Stride{};
    };

    class StubVertexBuffer : public Cocoa::Graphics::VertexBuffer
    {
    public:
        StubVertexBuffer(uint32_t size, const Cocoa::Graphics::BufferLayout& bufferLayout, VertexBufferCapture& vertexBufferCapture);
        StubVertexBuffer(const void* vertices, uint32_t size, const Cocoa::Graphics::BufferLayout& bufferLayout, VertexBufferCapture& vertexBufferCapture);
        ~StubVertexBuffer() override;
        void Bind() const override;
        void Unbind() const override;
        void SetData(const void* data, uint32_t size) const override;
        [[nodiscard]] const Cocoa::Graphics::BufferLayout& GetLayout() const override;

    private:
        Cocoa::Graphics::BufferLayout m_bufferLayout;
        VertexBufferCapture& m_vertexBufferCapture;
    };
}