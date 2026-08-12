#pragma once

#include <cassert>
#include <cstdint>

namespace Cocoa::Graphics
{
    struct Viewport
    {
        int32_t X;
        int32_t Y;
        uint32_t Width;
        uint32_t Height;

        Viewport(const int32_t x, const int32_t y, const uint32_t width, const uint32_t height) :
            X(x),
            Y(y),
            Width(width),
            Height(height)
        {

        }

        void Resize(
            const int32_t x,
            const int32_t y,
            const uint32_t width,
            const uint32_t height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }

        [[nodiscard]] float GetAspectRatio() const
        {
            assert(Height != 0 && "Viewport::GetAspectRatio() cannot divide by zero height");
            return static_cast<float>(Width) / static_cast<float>(Height);
        }
    };
}
