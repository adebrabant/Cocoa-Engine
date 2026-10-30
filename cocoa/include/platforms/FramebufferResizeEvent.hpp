#pragma once
#include <cstdint>

namespace cocoa::Platforms
{
    struct FramebufferResizeEvent
    {
        uint32_t Width;
        uint32_t Height;
    };
}
