#pragma once

#include <cstdint>

namespace Cocoa::Graphics
{
    struct FramebufferSpec
    {
        uint32_t Width{};
        uint32_t Height{};
    };

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
    };
}
