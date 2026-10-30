#pragma once

#include <cstdint>
#include <graphics/BufferLayout.hpp>
#include <graphics/VertexBuffer.hpp>

namespace CocoaBenchmarks
{
    class StubVertexBuffer : public cocoa::Graphics::VertexBuffer
    {
    public:
        StubVertexBuffer(uint32_t size, const cocoa::Graphics::BufferLayout& bufferLayout)
            : m_bufferLayout(bufferLayout) { }
        StubVertexBuffer(const void* vertices, uint32_t size, const cocoa::Graphics::BufferLayout& bufferLayout)
            : m_bufferLayout(bufferLayout) { }
        ~StubVertexBuffer() override = default;
        void Bind() const override { }
        void Unbind() const override { }
        void SetData(const void* data, uint32_t size) const override { }

        [[nodiscard]] const cocoa::Graphics::BufferLayout& GetLayout() const override { return m_bufferLayout;}

    private:
        cocoa::Graphics::BufferLayout m_bufferLayout;
    };
}