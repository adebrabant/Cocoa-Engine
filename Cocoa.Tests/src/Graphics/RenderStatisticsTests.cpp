#include <Graphics/RenderStatistics.hpp>
#include <gtest/gtest.h>
#include <cstdint>

namespace Cocoa::Graphics::Tests
{
    TEST(RenderStatisticsTests, Reset_ShouldSetAllCountsToZero_WhenCalled)
    {
        Graphics::RenderStatistics sut;
        sut.VertexCount = 3;
        sut.IndexCount = 6;
        sut.DrawCount = 10;
        sut.BatchFlushCount = 20;

        sut.Reset();

        ASSERT_EQ(0, sut.VertexCount);
        ASSERT_EQ(0, sut.IndexCount);
        ASSERT_EQ(0, sut.DrawCount);
        ASSERT_EQ(0, sut.BatchFlushCount);
    }
}