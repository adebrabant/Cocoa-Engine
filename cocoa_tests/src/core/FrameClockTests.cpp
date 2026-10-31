#include "../../../cocoa/include/core/FrameClock.hpp"
#include <chrono>
#include <gtest/gtest.h>
#include <thread>

namespace cocoa_tests::core
{
    TEST(FrameClockTests, Tick_ShouldIncreaseAccumulator_WhenCalled)
    {
        cocoa::core::FrameClock sut(0.25f, 0.1f);
        float alphaBefore = sut.getAlpha();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sut.tick();

        EXPECT_GT(sut.getAlpha(), alphaBefore);
    }

    TEST(FrameClockTests, CanUpdate_ShouldReturnTrue_WhenAccumulatorExceedsFixedDelta)
    {
        cocoa::core::FrameClock sut(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        sut.tick();

        EXPECT_TRUE(sut.canUpdate());
    }

    TEST(FrameClockTests, CanUpdate_ShouldReturnFalse_WhenAccumulatorIsBelowFixedDelta)
    {
        cocoa::core::FrameClock sut(0.25f, 0.5f);

        sut.tick();

        EXPECT_FALSE(sut.canUpdate());
    }

    TEST(FrameClockTests, ConsumeUpdate_ShouldReduceAccumulator_WhenCanUpdate)
    {
        cocoa::core::FrameClock sut(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        sut.tick();

        float alphaBefore = sut.getAlpha();
        if (sut.canUpdate())
            sut.consumeUpdate();

        EXPECT_LT(sut.getAlpha(), alphaBefore + 0.001f);
    }

    TEST(FrameClockTests, GetDelta_ShouldReturnDelta_WhenPositive)
    {
        cocoa::core::FrameClock sut(0.25f, 1.0f / 60.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sut.tick();

        EXPECT_GT(sut.getDelta(), 0.0f);
        EXPECT_LE(sut.getDelta(), 0.25f);
    }

    TEST(FrameClockTests, GetFixedDelta_ShouldReturnFixedDelta_WhenPositive)
    {
        cocoa::core::FrameClock sut(0.25f, 0.1f);

        EXPECT_FLOAT_EQ(sut.getFixedDelta(), 0.1f);
    }

    TEST(FrameClockTests, GetFixedDelta_ShouldReturnDeltaTime_WhenFixedDeltaZero)
    {
        cocoa::core::FrameClock sut(0.25f, 0.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sut.tick();

        EXPECT_GT(sut.getFixedDelta(), 0.0f);
    }

    TEST(FrameClockTests, GetAlpha_ShouldClampBetweenZeroAndOne)
    {
        cocoa::core::FrameClock sut(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        sut.tick();

        float alpha = sut.getAlpha();
        EXPECT_GE(alpha, 0.0f);
        EXPECT_LE(alpha, 1.0f);
    }

    TEST(FrameClockTests, Reset_ShouldZeroAccumulatorAndDeltaTime)
    {
        cocoa::core::FrameClock sut(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        sut.tick();

        sut.reset();
        EXPECT_FLOAT_EQ(sut.getAlpha(), 0.0f);
        EXPECT_FALSE(sut.canUpdate());
    }

    TEST(FrameClockTests, GetElapsed_ShouldIncreaseOverTime)
    {
        cocoa::core::FrameClock sut(0.25f, 0.05f);

        auto elapsed1 = sut.getElapsed();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        auto elapsed2 = sut.getElapsed();

        EXPECT_GT(elapsed2, elapsed1);
    }

    TEST(FrameClockTests, SleepNextFrame_ShouldSleepAtLeastTargetTime_WhenDeltaLessThanTarget)
    {
        cocoa::core::FrameClock sut(0.25f, 0.05f, 1.0f / 60.0f);

        auto start = std::chrono::high_resolution_clock::now();
        sut.sleepNextFrame();
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> elapsed = end - start;
        constexpr float tolerance = 0.04f;
        EXPECT_GE(elapsed.count() + tolerance, sut.getFixedDelta());
    }

    TEST(FrameClockTests, GetRemainingFrameTime_ShouldReturnRemainingFrameTime_WhenTargetFrameTimeIsGreaterThanZero)
    {
        cocoa::core::FrameClock sut(0.25f, 0.05f, 1.0f/ 60.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        sut.tick();
        const auto result = sut.getRemainingFrameTime();

        EXPECT_TRUE(result > 0.0f);
    }

    TEST(FrameClockTests, GetRemainingFrameTime_ShouldReturnZero_WhenTargetFrameTimeIsEqualOrLessThanZero)
    {
        const cocoa::core::FrameClock sut(0.25f, 0.05f, 0.0f);

        const auto result = sut.getRemainingFrameTime();

        EXPECT_TRUE(result <= 0.0f);
    }
}
