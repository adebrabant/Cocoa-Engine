#pragma once

#include <graphics/Framebuffer.hpp>

namespace cocoa_benchmarks
{
    class StubFramebuffer : public cocoa::graphics::Framebuffer
    {
    public:
        explicit StubFramebuffer(cocoa::graphics::FramebufferSpec spec) { }
        ~StubFramebuffer() override = default;

        void UnBind() const override { }
        void Bind() const override { }
        void Resize(uint32_t width, uint32_t height) override { }
    };
}
