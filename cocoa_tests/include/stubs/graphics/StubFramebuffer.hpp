#pragma once

#include <graphics/Framebuffer.hpp>

namespace cocoa_tests::stubs
{
    class StubFramebuffer : public cocoa::graphics::Framebuffer
    {
    public:
        explicit StubFramebuffer(const cocoa::graphics::FramebufferSpec& spec) { }
        ~StubFramebuffer() override = default;

        void unBind() const override { }
        void bind() const override { }
        void resize(uint32_t width, uint32_t height) override { }
    };
}
