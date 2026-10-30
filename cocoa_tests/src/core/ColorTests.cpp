#include <core/Color.hpp>
#include <gtest/gtest.h>

namespace CocoaTests::Core
{
    struct ColorTestCase
    {
        cocoa::Core::Color Other;
        bool Expected;
    };
    class ColorOperatorTests : public testing::TestWithParam<ColorTestCase> {};
    INSTANTIATE_TEST_SUITE_P(
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
        constexpr cocoa::Core::Color sut{1.0f, 0.5f, 0.2f, 1.0f};

        const bool result = sut == testCase.Other;

        EXPECT_EQ(testCase.Expected, result);
    }
}