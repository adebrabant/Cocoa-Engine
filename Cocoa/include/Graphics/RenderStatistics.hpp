#pragma once

#include "Graphics/SortLayer.hpp"

#include <cstdint>
#include <vector>

namespace Cocoa::Graphics
{
    enum class DrawSubmissionType
    {
        RawQuad,
        Sprite
    };

    struct DrawSubmissionInfo
    {
        size_t Index;
        int SortingOrder;
        SortLayer SortingLayer;
        DrawSubmissionType SubmissionType;
    };

    // TODO: Look into enable flags for debug vs release modes
    struct RenderStatistics
    {
        uint32_t DrawCount{ 0 };
        uint32_t VertexCount{ 0 };
        uint32_t IndexCount{ 0 };
        uint32_t BatchFlushCount{ 0 };
        std::vector<DrawSubmissionInfo> DrawSubmissionsInfo;

        void Reset()
        {
            DrawCount = 0;
            VertexCount = 0;
            IndexCount = 0;
            BatchFlushCount = 0;
            DrawSubmissionsInfo.clear();
        }
    };
}
