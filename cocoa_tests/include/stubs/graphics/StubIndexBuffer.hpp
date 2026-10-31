#pragma once

#include <cstdint>
#include <graphics/IndexBuffer.hpp>

namespace cocoa_tests::stubs
{
    class StubIndexBuffer : public cocoa::graphics::IndexBuffer
    {
    public:
        StubIndexBuffer(const uint32_t* indices, uint32_t count);
        ~StubIndexBuffer() override;
        void bind() const override;
        void unbind() const override;
        [[nodiscard]] uint32_t getCount() const override;

    private:
        uint32_t m_count;
    };
}
