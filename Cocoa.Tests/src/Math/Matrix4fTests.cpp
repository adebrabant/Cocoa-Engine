#include <Math/Matrix4f.hpp>
#include <Math/Vector4f.hpp>
#include <gtest/gtest.h>

namespace Cocoa::Math::Tests
{
    TEST(Matrix4fTests, Constructor_ShouldSetElementsToZero_WhenUsingDefaultConstructor)
    {
        constexpr Matrix4f sut;

        for (std::size_t i = 0; i <= 15; ++i)
        {
            EXPECT_FLOAT_EQ(sut[i], 0) << "Element index: " << i;
        }
    }

    TEST(Matrix4fTests, Constructor_ShouldSetElements_WhenProvidingValues)
    {
        constexpr std::array<float, 16> expectedElements{
            2.0f, 4.0f, 6.0f, 8.0f,
            10.0f, 12.0f, 14.0f, 16.0f,
            18.0f, 20.0f, 22.0f, 24.0f,
            26.0f, 28.0f, 30.0f, 32.0f
        };

        constexpr Matrix4f sut(
            expectedElements[0], expectedElements[1], expectedElements[2], expectedElements[3],
            expectedElements[4], expectedElements[5], expectedElements[6], expectedElements[7],
            expectedElements[8], expectedElements[9], expectedElements[10], expectedElements[11],
            expectedElements[12], expectedElements[13], expectedElements[14], expectedElements[15]
        );

        for (std::size_t i = 0; i < expectedElements.size(); ++i)
        {
            EXPECT_FLOAT_EQ(sut[i], expectedElements[i]) << "Element index: " << i;
        }
    }

    TEST(Matrix4fTests, AddOperator_ShouldReturnSum_WhenAddingTwoMatrices)
    {
        constexpr Matrix4f sut(
            2.0f, 3.0f, 4.0f, 5.0f,
            6.0f, 7.0f, 8.0f, 9.0f,
            10.0f, 11.0f, 12.0f, 13.0f,
            14.0f, 15.0f, 16.0f, 17.0f
        );
        constexpr Matrix4f other(
            2.5f, 3.5f, 4.5f, 5.5f,
            6.5f, 7.5f, 8.5f, 9.5f,
            10.5f, 11.5f, 12.5f, 13.5f,
            14.5f, 15.5f, 16.5f, 17.5f
        );

        constexpr Matrix4f result = sut + other;

        EXPECT_FLOAT_EQ(result[0], 4.5f);
        EXPECT_FLOAT_EQ(result[1], 6.5f);
        EXPECT_FLOAT_EQ(result[2], 8.5f);
        EXPECT_FLOAT_EQ(result[3], 10.5f);
        EXPECT_FLOAT_EQ(result[4], 12.5f);
        EXPECT_FLOAT_EQ(result[5], 14.5f);
        EXPECT_FLOAT_EQ(result[6], 16.5f);
        EXPECT_FLOAT_EQ(result[7], 18.5f);
        EXPECT_FLOAT_EQ(result[8], 20.5f);
        EXPECT_FLOAT_EQ(result[9], 22.5f);
        EXPECT_FLOAT_EQ(result[10], 24.5f);
        EXPECT_FLOAT_EQ(result[11], 26.5f);
        EXPECT_FLOAT_EQ(result[12], 28.5f);
        EXPECT_FLOAT_EQ(result[13], 30.5f);
        EXPECT_FLOAT_EQ(result[14], 32.5f);
        EXPECT_FLOAT_EQ(result[15], 34.5f);
    }

    TEST(Matrix4fTests, SubtractOperator_ShouldReturnDifference_WhenSubtractingTwoMatrices)
    {
        constexpr Matrix4f sut(
            2.0f, 3.0f, 4.0f, 5.0f,
            6.0f, 7.0f, 8.0f, 9.0f,
            10.0f, 11.0f, 12.0f, 13.0f,
            14.0f, 15.0f, 16.0f, 17.0f
        );
        constexpr Matrix4f other(
            2.5f, 3.5f, 4.5f, 5.5f,
            6.5f, 7.5f, 8.5f, 9.5f,
            10.5f, 11.5f, 12.5f, 13.5f,
            14.5f, 15.5f, 16.5f, 17.5f
        );

        constexpr Matrix4f result = sut - other;

        for (std::size_t i = 0; i < 16; ++i)
        {
            EXPECT_FLOAT_EQ(result[i], -0.5f) << "Element index: " << i;
        }
    }

    TEST(Matrix4fTests, MultiplyOperator_ShouldScaleMatrix_WhenMultiplyingByScalar)
    {
        constexpr Matrix4f sut(
            2.0f, 3.0f, 4.0f, 5.0f,
            6.0f, 7.0f, 8.0f, 9.0f,
            10.0f, 11.0f, 12.0f, 13.0f,
            14.0f, 15.0f, 16.0f, 17.0f
        );
        constexpr float scalar = 5.0f;

        constexpr Matrix4f result = sut * scalar;

        EXPECT_FLOAT_EQ(result[0], 10.0f);
        EXPECT_FLOAT_EQ(result[1], 15.0f);
        EXPECT_FLOAT_EQ(result[2], 20.0f);
        EXPECT_FLOAT_EQ(result[3], 25.0f);
        EXPECT_FLOAT_EQ(result[4], 30.0f);
        EXPECT_FLOAT_EQ(result[5], 35.0f);
        EXPECT_FLOAT_EQ(result[6], 40.0f);
        EXPECT_FLOAT_EQ(result[7], 45.0f);
        EXPECT_FLOAT_EQ(result[8], 50.0f);
        EXPECT_FLOAT_EQ(result[9], 55.0f);
        EXPECT_FLOAT_EQ(result[10], 60.0f);
        EXPECT_FLOAT_EQ(result[11], 65.0f);
        EXPECT_FLOAT_EQ(result[12], 70.0f);
        EXPECT_FLOAT_EQ(result[13], 75.0f);
        EXPECT_FLOAT_EQ(result[14], 80.0f);
        EXPECT_FLOAT_EQ(result[15], 85.0f);
    }

    TEST(Matrix4fTests, MultiplyOperator_ShouldReturnProduct_WhenMultiplyingTwoMatrices)
    {
        constexpr Matrix4f sut(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        );
        constexpr Matrix4f other(
            17.0f, 18.0f, 19.0f, 20.0f,
            21.0f, 22.0f, 23.0f, 24.0f,
            25.0f, 26.0f, 27.0f, 28.0f,
            29.0f, 30.0f, 31.0f, 32.0f
        );

        constexpr Matrix4f result = sut * other;

        EXPECT_FLOAT_EQ(result[0], 538.0f);
        EXPECT_FLOAT_EQ(result[1], 612.0f);
        EXPECT_FLOAT_EQ(result[2], 686.0f);
        EXPECT_FLOAT_EQ(result[3], 760.0f);

        EXPECT_FLOAT_EQ(result[4], 650.0f);
        EXPECT_FLOAT_EQ(result[5], 740.0f);
        EXPECT_FLOAT_EQ(result[6], 830.0f);
        EXPECT_FLOAT_EQ(result[7], 920.0f);

        EXPECT_FLOAT_EQ(result[8], 762.0f);
        EXPECT_FLOAT_EQ(result[9], 868.0f);
        EXPECT_FLOAT_EQ(result[10], 974.0f);
        EXPECT_FLOAT_EQ(result[11], 1080.0f);

        EXPECT_FLOAT_EQ(result[12], 874.0f);
        EXPECT_FLOAT_EQ(result[13], 996.0f);
        EXPECT_FLOAT_EQ(result[14], 1118.0f);
        EXPECT_FLOAT_EQ(result[15], 1240.0f);
    }
}