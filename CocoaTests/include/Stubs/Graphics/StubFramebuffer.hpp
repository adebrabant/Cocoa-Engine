#pragma once

#include <Graphics/Framebuffer.hpp>

namespace CocoaTests::Stubs
{
    class StubFramebuffer : public Cocoa::Graphics::Framebuffer
    {
    public:
        explicit StubFramebuffer(const Cocoa::Graphics::FramebufferSpec& spec) { }
        ~StubFramebuffer() override = default;

        void UnBind() const override { }
        void Bind() const override { }
    };
}