#include <Math/Matrix2f.hpp>

#include <gtest/gtest.h>
#include <numbers>

namespace Cocoa::Math::Tests
{
    TEST(Matrix2fTests, constexprructor_ShouldSetElementsToZero_WhenUsingDefaultconstexprructor)
    {
        constexpr Matrix2f sut;

        for (std::size_t i = 0; i <= 3; ++i)
        {
            EXPECT_FLOAT_EQ(sut[i], 0.0f);
        }
    }

    TEST(Matrix2fTests, constexprructor_ShouldSetElements_WhenProvidingValues)
    {
        constexpr float expectedM00 = 2.0f;
        constexpr float expectedM01 = 2.0f;
        constexpr float expectedM10 = 2.0f;
        constexpr float expectedM11 = 2.0f;

        constexpr Matrix2f sut(
            expectedM00, expectedM10,
            expectedM01, expectedM11
        );

        EXPECT_FLOAT_EQ(sut[0], expectedM00);
        EXPECT_FLOAT_EQ(sut[2], expectedM01);
        EXPECT_FLOAT_EQ(sut[1], expectedM10);
        EXPECT_FLOAT_EQ(sut[3], expectedM11);
    }

    TEST(Matrix2fTests, AddOperator_ShouldReturnSum_WhenAddingTwoMatrices)
    {
        constexpr Matrix2f sut(2.0f, 3.0f, 4.0f, 5.0f);
        constexpr Matrix2f other(2.5f, 3.6f, 4.7f, 5.8f);

        constexpr Matrix2f result = sut + other;

        EXPECT_FLOAT_EQ(result[0], 4.5f);
        EXPECT_FLOAT_EQ(result[1], 6.6f);
        EXPECT_FLOAT_EQ(result[2], 8.7f);
        EXPECT_FLOAT_EQ(result[3], 10.8f);
    }

    TEST(Matrix2fTests, SubtractOperator_ShouldReturnDifference_WhenSubtractingTwoMatrics)
    {
        constexpr Matrix2f sut(2.0f, 3.0f, 4.0f, 5.8f);
        constexpr Matrix2f other(2.5f, 3.6f, 4.7f, 5.0f);

        constexpr Matrix2f result = sut - other;

        EXPECT_FLOAT_EQ(result[0], -0.5f);
        EXPECT_FLOAT_EQ(result[1], -0.6f);
        EXPECT_FLOAT_EQ(result[2], -0.7f);
        EXPECT_FLOAT_EQ(result[3], 0.8f);
    }

    TEST(Matrix2fTests, MultiplyOperator_ShouldScaleMatrix_WhenMultiplyingByScalar)
    {
        constexpr Matrix2f sut(2.0f, 3.0f, 4.0f, 5.8f);
        constexpr float scalar = 5.0f;

        constexpr Matrix2f result = sut * scalar;

        EXPECT_FLOAT_EQ(result[0], 10.0f);
        EXPECT_FLOAT_EQ(result[1], 15.0f);
        EXPECT_FLOAT_EQ(result[2], 20.0f);
        EXPECT_FLOAT_EQ(result[3], 29.0f);
    }

    TEST(Matrix2fTests, MultiplyOperator_ShouldReturnProduct_WhenMultiplyingTwoMatrices)
    {
        constexpr Matrix2f sut(
            5.0f, 7.0f,
            6.0f, 8.8f
        );
        constexpr Matrix2f other(
            9.0f, 11.0f,
            10.0f, 12.0f
        );

        constexpr Matrix2f result = sut * other;

        EXPECT_FLOAT_EQ(result[0], 111.0f);
        EXPECT_FLOAT_EQ(result[2], 122.0f);
        EXPECT_FLOAT_EQ(result[1], 159.8f);
        EXPECT_FLOAT_EQ(result[3], 175.6f);
    }

    TEST(Matrix2fTests, MultiplyOperator_ShouldReturnVectorProduct_WhenMultiplyingByVector)
    {
        constexpr Vector2f scale(3.0f, 2.0f);
        constexpr Matrix2f sut(
            1.0f, 3.0f,
            2.0f, 4.0f
        );

        constexpr Vector2f result = sut * scale;

        EXPECT_FLOAT_EQ(result.X, 7.0f);
        EXPECT_FLOAT_EQ(result.Y, 17.0f);
    }

    TEST(Matrix2fTests, Identity_ShouldReturnDefaults_WhenCalled)
    {
        constexpr Matrix2f result = Matrix2f::Identity();

        EXPECT_FLOAT_EQ(result[0], 1.0f);
        EXPECT_FLOAT_EQ(result[1], 0.0f);
        EXPECT_FLOAT_EQ(result[2], 0.0f);
        EXPECT_FLOAT_EQ(result[3], 1.0f);
    }

    TEST(Matrix2fTests, Scale_ShouldReturnScaleMatrix_WhenCalled)
    {
        constexpr Vector2f scale(2.0f, 3.0f);

        constexpr Matrix2f result = Matrix2f::Scale(scale);

        EXPECT_FLOAT_EQ(result[0], scale.X);
        EXPECT_FLOAT_EQ(result[1], 0.0f);
        EXPECT_FLOAT_EQ(result[2], 0.0f);
        EXPECT_FLOAT_EQ(result[3], scale.Y);
    }

    TEST(Matrix2fTests, Rotation_ShouldRotateVectorCounterClockwise)
    {
        constexpr float angle = std::numbers::pi_v<float> / 2.0f;
        constexpr Vector2f vector(0.0f, 4.0f);

        const Matrix2f sut = Matrix2f::Rotation(angle);
        const Vector2f result = sut * vector;

        EXPECT_NEAR(result.X, -4.0f, 0.0001f);
        EXPECT_NEAR(result.Y, 0.0f, 0.0001f);
    }
}
