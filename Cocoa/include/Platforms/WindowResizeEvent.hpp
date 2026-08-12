#pragma once
#include <cstdint>

namespace Cocoa::Platforms
{
    struct WindowResizeEvent
    {
        uint32_t Width;
        uint32_t Height;
    };
}
