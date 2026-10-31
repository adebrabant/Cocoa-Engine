#pragma once

#include <cstdint>
#include <graphics/BufferLayout.hpp>
#include <graphics/VertexBuffer.hpp>

namespace cocoa_benchmarks
{
    class StubVertexBuffer : public cocoa::graphics::VertexBuffer
    {
    public:
        StubVertexBuffer(uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout)
            : m_bufferLayout(bufferLayout) { }
        StubVertexBuffer(const void* vertices, uint32_t size, const cocoa::graphics::BufferLayout& bufferLayout)
            : m_bufferLayout(bufferLayout) { }
        ~StubVertexBuffer() override = default;
        void bind() const override { }
        void unbind() const override { }
        void setData(const void* data, uint32_t size) const override { }

        [[nodiscard]] const cocoa::graphics::BufferLayout& getLayout() const override { return m_bufferLayout;}

    private:
        cocoa::graphics::BufferLayout m_bufferLayout;
    };
}
