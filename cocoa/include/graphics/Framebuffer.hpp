#pragma once

#include <cstdint>
#include <vector>

namespace cocoa::graphics
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
        uint32_t width{};
        uint32_t height{};
        std::vector<ColorFormat> colorFormats{};
        DepthStencilFormat depthStencilFormat{ DepthStencilFormat::None };
    };

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;
        virtual void bind() const = 0;
        virtual void unBind() const = 0;
        virtual void resize(uint32_t width, uint32_t height) = 0;
    };
}
