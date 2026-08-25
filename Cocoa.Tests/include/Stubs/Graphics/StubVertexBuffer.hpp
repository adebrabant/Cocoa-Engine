#pragma once

#include <cstdint>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/BufferLayout.hpp>

namespace Cocoa::Stubs
{
    class StubVertexBuffer : public Graphics::VertexBuffer
    {
    public:
        StubVertexBuffer(uint32_t size, const Graphics::BufferLayout& bufferLayout);
        StubVertexBuffer(const void* vertices, uint32_t size, const Graphics::BufferLayout& bufferLayout);
        ~StubVertexBuffer() override;
        void Bind() const override;
        void Unbind() const override;
        void SetData(const void* data, uint32_t size) const override;
        [[nodiscard]] const Graphics::BufferLayout& GetLayout() const override;

    private:
        Graphics::BufferLayout m_bufferLayout;
    };
}