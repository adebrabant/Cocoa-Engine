#pragma once
#include <cstdint>

namespace cocoa::platforms
{
    struct FramebufferResizeEvent
    {
        uint32_t width;
        uint32_t height;
    };
}
