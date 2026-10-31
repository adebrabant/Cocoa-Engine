#pragma once

#include <cstdint>
#include <cstring>

namespace cocoa::graphics
{
    struct RenderStatistics
    {
        uint32_t drawCount{ 0 };
        uint32_t vertexCount{ 0 };
        uint32_t indexCount{ 0 };
        uint32_t batchFlushCount{ 0 };

        void reset()
        {
            std::memset(this, 0, sizeof(*this));
        }
    };
}
