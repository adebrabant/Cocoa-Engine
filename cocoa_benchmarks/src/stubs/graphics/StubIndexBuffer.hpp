#pragma once

#include <cstdint>
#include <graphics/IndexBuffer.hpp>

namespace CocoaBenchmarks
{
    class StubIndexBuffer : public cocoa::Graphics::IndexBuffer
    {
    public:
        StubIndexBuffer(const uint32_t* indices, uint32_t count) : m_count(count) { }
        ~StubIndexBuffer() override = default;
        void Bind() const override { }
        void Unbind() const override { }
        [[nodiscard]] uint32_t GetCount() const override {return m_count;}

    private:
        uint32_t m_count;
    };
}