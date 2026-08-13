#pragma once
#include <cstdint>

namespace Cocoa::Platforms
{
    struct FramebufferResizeEvent
    {
        uint32_t Width;
        uint32_t Height;
    };
}
