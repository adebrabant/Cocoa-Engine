#pragma once

#include <cstdint>
#include <cstring>

namespace Cocoa::Graphics
{
    struct RenderStatistics
    {
        uint32_t DrawCount{ 0 };
        uint32_t VertexCount{ 0 };
        uint32_t IndexCount{ 0 };
        uint32_t BatchFlushCount{ 0 };

        void Reset()
        {
            memset(this, 0, sizeof(*this));
        }
    };
}
