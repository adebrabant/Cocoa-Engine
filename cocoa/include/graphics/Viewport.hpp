#pragma once

#include <cassert>
#include <cstdint>

namespace cocoa::graphics
{
    struct Viewport
    {
        int32_t x;
        int32_t y;
        uint32_t width;
        uint32_t height;

        Viewport(const int32_t x, const int32_t y, const uint32_t width, const uint32_t height) :
            x(x),
            y(y),
            width(width),
            height(height)
        {
            assert(height != 0 && "Viewport::Viewport() height cannot be zero");
        }

        void resize(
            const int32_t newX,
            const int32_t newY,
            const uint32_t newWidth,
            const uint32_t newHeight)
        {
            assert(newHeight != 0 && "Viewport::resize() height cannot be zero");
            x = newX;
            y = newY;
            width = newWidth;
            height = newHeight;
        }

        [[nodiscard]] float GetAspectRatio() const
        {
            assert(height != 0 && "Viewport::GetAspectRatio() cannot divide by zero height");
            return static_cast<float>(width) / static_cast<float>(height);
        }
    };
}
