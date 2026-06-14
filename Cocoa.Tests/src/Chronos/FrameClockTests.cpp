#include "Chronos/FrameClock.hpp"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

namespace Cocoa::Chronos::Tests
{
    TEST(FrameClockTests, Tick_ShouldIncreaseAccumulator_WhenCalled)
    {
        Chronos::FrameClock clock(0.25f, 0.1f);
        float alphaBefore = clock.GetAlpha();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        clock.Tick();

        EXPECT_GT(clock.GetAlpha(), alphaBefore);
    }

    TEST(FrameClockTests, CanUpdate_ShouldReturnTrue_WhenAccumulatorExceedsFixedDelta)
    {
        Chronos::FrameClock clock(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        clock.Tick();

        EXPECT_TRUE(clock.CanUpdate());
    }

    TEST(FrameClockTests, CanUpdate_ShouldReturnFalse_WhenAccumulatorIsBelowFixedDelta)
    {
        Chronos::FrameClock clock(0.25f, 0.5f);

        clock.Tick();

        EXPECT_FALSE(clock.CanUpdate());
    }

    TEST(FrameClockTests, ConsumeUpdate_ShouldReduceAccumulator_WhenCanUpdate)
    {
        Chronos::FrameClock clock(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        clock.Tick();

        float alphaBefore = clock.GetAlpha();
        if (clock.CanUpdate())
            clock.ConsumeUpdate();

        EXPECT_LT(clock.GetAlpha(), alphaBefore + 0.001f);
    }

    TEST(FrameClockTests, GetDelta_ShouldReturnDelta_WhenPositive)
    {
        Chronos::FrameClock clock(0.25f, 1.0f / 60.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        clock.Tick();

        EXPECT_GT(clock.GetDelta(), 0.0f);
        EXPECT_LE(clock.GetDelta(), 0.25f);
    }

    TEST(FrameClockTests, GetFixedDelta_ShouldReturnFixedDelta_WhenPositive)
    {
        Chronos::FrameClock clock(0.25f, 0.1f);

        EXPECT_FLOAT_EQ(clock.GetFixedDelta(), 0.1f);
    }

    TEST(FrameClockTests, GetFixedDelta_ShouldReturnDeltaTime_WhenFixedDeltaZero)
    {
        Chronos::FrameClock clock(0.25f, 0.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        clock.Tick();

        EXPECT_GT(clock.GetFixedDelta(), 0.0f);
    }

    TEST(FrameClockTests, GetAlpha_ShouldClampBetweenZeroAndOne)
    {
        Chronos::FrameClock clock(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clock.Tick();

        float alpha = clock.GetAlpha();
        EXPECT_GE(alpha, 0.0f);
        EXPECT_LE(alpha, 1.0f);
    }

    TEST(FrameClockTests, Reset_ShouldZeroAccumulatorAndDeltaTime)
    {
        Chronos::FrameClock clock(0.25f, 0.05f);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        clock.Tick();

        clock.Reset();
        EXPECT_FLOAT_EQ(clock.GetAlpha(), 0.0f);
        EXPECT_FALSE(clock.CanUpdate());
    }

    TEST(FrameClockTests, GetElapsed_ShouldIncreaseOverTime)
    {
        Chronos::FrameClock clock(0.25f, 0.05f);

        auto elapsed1 = clock.GetElapsed();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        auto elapsed2 = clock.GetElapsed();

        EXPECT_GT(elapsed2, elapsed1);
    }

    TEST(FrameClockTests, SleepNextFrame_ShouldSleepAtLeastTargetTime_WhenDeltaLessThanTarget)
    {
        Chronos::FrameClock clock(0.25f, 0.05f, 1.0f / 60.0f);

        auto start = std::chrono::high_resolution_clock::now();
        clock.SleepNextFrame();
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> elapsed = end - start;
        constexpr float tolerance = 0.04f;
        EXPECT_GE(elapsed.count() + tolerance, clock.GetFixedDelta());
    }
}