#pragma once

#include <graphics/Framebuffer.hpp>

namespace CocoaBenchmarks
{
    class StubFramebuffer : public cocoa::Graphics::Framebuffer
    {
    public:
        explicit StubFramebuffer(cocoa::Graphics::FramebufferSpec spec) { }
        ~StubFramebuffer() override = default;

        void UnBind() const override { }
        void Bind() const override { }
        void Resize(uint32_t width, uint32_t height) override { }
    };
}