#pragma once
#include <cstdint>

namespace cocoa::platforms
{
    struct FramebufferResizeEvent
    {
        uint32_t Width;
        uint32_t Height;
    };
}
