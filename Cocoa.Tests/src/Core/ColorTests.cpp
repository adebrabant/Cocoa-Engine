#include <Core/Color.hpp>
#include <gtest/gtest.h>

namespace Cocoa::Core::Tests
{
    struct ColorTestCase
    {
        Color Other;
        bool Expected;
    };
    class ColorOperatorTests : public testing::TestWithParam<ColorTestCase> {};
    INSTANTIATE_TEST_CASE_P(
        ColorValues,
        ColorOperatorTests,
        testing::Values
        (
            ColorTestCase
            {
                .Other{1.0f, 0.5f, 0.2f, 1.0f},
                .Expected = true
            },
            ColorTestCase
            {
                .Other{0.0f, 0.5f, 0.2f, 1.0f},
                .Expected = false
            },
            ColorTestCase
            {
                .Other{1.0f, 0.1f, 0.2f, 1.0f},
                .Expected = false
            },
            ColorTestCase
            {
                .Other{1.0f, 0.5f, 0.8f, 1.0f},
                .Expected = false
            },
            ColorTestCase
            {
                .Other{1.0f, 0.5f, 0.2f, 0.0f},
                .Expected = false
            }
        )
    );
    TEST_P(ColorOperatorTests, BoolOperator_ShouldReturnExpectedValue)
    {
        const ColorTestCase testCase = GetParam();
        constexpr Color sut{1.0f, 0.5f, 0.2f, 1.0f};

        const bool result = sut == testCase.Other;

        EXPECT_EQ(testCase.Expected, result);
    }
}