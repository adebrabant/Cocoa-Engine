#pragma once

#include <cstdint>
#include <vector>

namespace Cocoa::Graphics
{
    enum class ColorFormat
    {
        RGBA8,
        RGB8,
        RGBA16F
    };

    enum class DepthStencilFormat
    {
        None,
        Depth24,
        Stencil8,
        Depth24Stencil8
    };

    struct FramebufferSpec
    {
        uint32_t Width{};
        uint32_t Height{};
        std::vector<ColorFormat> ColorFormats{};
        DepthStencilFormat DepthStencil{ DepthStencilFormat::None };
    };

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
    };
}
