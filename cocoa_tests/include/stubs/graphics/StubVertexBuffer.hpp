#pragma once

#include <graphics/BufferLayout.hpp>
#include <graphics/VertexBuffer.hpp>

#include <vector>

namespace cocoa_tests::stubs
{
    struct VertexBufferCapture
    {
        std::vector<std::byte> Data;
        size_t Stride{};
    };

    class StubVertexBuffer : public cocoa::graphics::VertexBuffer
    {
    public:
        StubVertexBuffer(uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout, VertexBufferCapture& vertexBufferCapture);
        StubVertexBuffer(const void* vertices, uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout, VertexBufferCapture& vertexBufferCapture);
        ~StubVertexBuffer() override;
        void bind() const override;
        void unbind() const override;
        void setData(const void* data, uint32_t size) const override;
        [[nodiscard]] const cocoa::graphics::BufferLayout& getLayout() const override;

    private:
        cocoa::graphics::BufferLayout m_bufferLayout;
        VertexBufferCapture& m_vertexBufferCapture;
    };
}
