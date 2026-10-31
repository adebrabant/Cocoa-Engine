#include <cstdint>
#include <graphics/RenderStatistics.hpp>
#include <gtest/gtest.h>

namespace cocoa_tests::graphics
{
    TEST(RenderStatisticsTests, Reset_ShouldSetAllCountsToZero_WhenCalled)
    {
        cocoa::graphics::RenderStatistics sut;
        sut.vertexCount = 3;
        sut.indexCount = 6;
        sut.drawCount = 10;
        sut.batchFlushCount = 20;

        sut.reset();

        ASSERT_EQ(0, sut.vertexCount);
        ASSERT_EQ(0, sut.indexCount);
        ASSERT_EQ(0, sut.drawCount);
        ASSERT_EQ(0, sut.batchFlushCount);
    }
}
