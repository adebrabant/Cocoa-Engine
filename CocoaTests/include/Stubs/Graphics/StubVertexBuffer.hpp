#pragma once

#include <cstdint>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/BufferLayout.hpp>

namespace CocoaTests::Stubs
{
    class StubVertexBuffer : public Cocoa::Graphics::VertexBuffer
    {
    public:
        StubVertexBuffer(uint32_t size, const Cocoa::Graphics::BufferLayout& bufferLayout);
        StubVertexBuffer(const void* vertices, uint32_t size, const Cocoa::Graphics::BufferLayout& bufferLayout);
        ~StubVertexBuffer() override;
        void Bind() const override;
        void Unbind() const override;
        void SetData(const void* data, uint32_t size) const override;
        [[nodiscard]] const Cocoa::Graphics::BufferLayout& GetLayout() const override;

    private:
        Cocoa::Graphics::BufferLayout m_bufferLayout;
    };
}