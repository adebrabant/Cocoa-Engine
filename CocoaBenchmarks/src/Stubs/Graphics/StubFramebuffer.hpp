#pragma once

#include <Graphics/Framebuffer.hpp>

namespace CocoaBenchmarks
{
    class StubFramebuffer : public Cocoa::Graphics::Framebuffer
    {
    public:
        explicit StubFramebuffer(Cocoa::Graphics::FramebufferSpec spec) { }
        ~StubFramebuffer() override = default;

        void UnBind() const override { }
        void Bind() const override { }
    };
}