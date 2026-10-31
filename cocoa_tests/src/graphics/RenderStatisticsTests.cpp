#include <cstdint>
#include <graphics/RenderStatistics.hpp>
#include <gtest/gtest.h>

namespace cocoa_tests::graphics
{
    TEST(RenderStatisticsTests, Reset_ShouldSetAllCountsToZero_WhenCalled)
    {
        cocoa::graphics::RenderStatistics sut;
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
