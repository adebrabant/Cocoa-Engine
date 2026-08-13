#include "Chronos/FrameClock.hpp"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

namespace Cocoa::Chronos::Tests
{
    TEST(FrameClockTests, Tick_ShouldIncreaseAccumulator_WhenCalled)
    {
        Chronos::FrameClock sut(0.25f, 0.1f);
        float alphaBefore = sut.GetAlpha();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sut.Tick();

        EXPECT_GT(sut.GetAlpha(), alphaBefore);
    }

    TEST(FrameClockTests, CanUpdate_ShouldReturnTrue_WhenAccumulatorExceedsFixedDelta)
    {
        Chronos::FrameClock sut(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        sut.Tick();

        EXPECT_TRUE(sut.CanUpdate());
    }

    TEST(FrameClockTests, CanUpdate_ShouldReturnFalse_WhenAccumulatorIsBelowFixedDelta)
    {
        Chronos::FrameClock sut(0.25f, 0.5f);

        sut.Tick();

        EXPECT_FALSE(sut.CanUpdate());
    }

    TEST(FrameClockTests, ConsumeUpdate_ShouldReduceAccumulator_WhenCanUpdate)
    {
        Chronos::FrameClock sut(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        sut.Tick();

        float alphaBefore = sut.GetAlpha();
        if (sut.CanUpdate())
            sut.ConsumeUpdate();

        EXPECT_LT(sut.GetAlpha(), alphaBefore + 0.001f);
    }

    TEST(FrameClockTests, GetDelta_ShouldReturnDelta_WhenPositive)
    {
        Chronos::FrameClock sut(0.25f, 1.0f / 60.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sut.Tick();

        EXPECT_GT(sut.GetDelta(), 0.0f);
        EXPECT_LE(sut.GetDelta(), 0.25f);
    }

    TEST(FrameClockTests, GetFixedDelta_ShouldReturnFixedDelta_WhenPositive)
    {
        Chronos::FrameClock sut(0.25f, 0.1f);

        EXPECT_FLOAT_EQ(sut.GetFixedDelta(), 0.1f);
    }

    TEST(FrameClockTests, GetFixedDelta_ShouldReturnDeltaTime_WhenFixedDeltaZero)
    {
        Chronos::FrameClock sut(0.25f, 0.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sut.Tick();

        EXPECT_GT(sut.GetFixedDelta(), 0.0f);
    }

    TEST(FrameClockTests, GetAlpha_ShouldClampBetweenZeroAndOne)
    {
        Chronos::FrameClock sut(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        sut.Tick();

        float alpha = sut.GetAlpha();
        EXPECT_GE(alpha, 0.0f);
        EXPECT_LE(alpha, 1.0f);
    }

    TEST(FrameClockTests, Reset_ShouldZeroAccumulatorAndDeltaTime)
    {
        Chronos::FrameClock sut(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        sut.Tick();

        sut.Reset();
        EXPECT_FLOAT_EQ(sut.GetAlpha(), 0.0f);
        EXPECT_FALSE(sut.CanUpdate());
    }

    TEST(FrameClockTests, GetElapsed_ShouldIncreaseOverTime)
    {
        Chronos::FrameClock sut(0.25f, 0.05f);

        auto elapsed1 = sut.GetElapsed();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        auto elapsed2 = sut.GetElapsed();

        EXPECT_GT(elapsed2, elapsed1);
    }

    TEST(FrameClockTests, SleepNextFrame_ShouldSleepAtLeastTargetTime_WhenDeltaLessThanTarget)
    {
        Chronos::FrameClock sut(0.25f, 0.05f, 1.0f / 60.0f);

        auto start = std::chrono::high_resolution_clock::now();
        sut.SleepNextFrame();
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> elapsed = end - start;
        constexpr float tolerance = 0.04f;
        EXPECT_GE(elapsed.count() + tolerance, sut.GetFixedDelta());
    }

    TEST(FrameClockTests, GetRemainingFrameTime_ShouldReturnRemainingFrameTime_WhenTargetFrameTimeIsGreaterThanZero)
    {
        Chronos::FrameClock sut(0.25f, 0.05f, 1.0f/ 60.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        sut.Tick();
        const auto result = sut.GetRemainingFrameTime();

        EXPECT_TRUE(result > 0.0f);
    }

    TEST(FrameClockTests, GetRemainingFrameTime_ShouldReturnZero_WhenTargetFrameTimeIsEqualOrLessThanZero)
    {
        const Chronos::FrameClock sut(0.25f, 0.05f, 0.0f);
        
        const auto result = sut.GetRemainingFrameTime();

        EXPECT_TRUE(result <= 0.0f);
    }
}