#include <Math/Matrix3f.hpp>

#include <gtest/gtest.h>

namespace Cocoa::Math::Tests
{
    TEST(Matrix3fTests, constexprructor_ShouldSetElementsToZero_WhenUsingDefaultconstexprructor)
    {
        constexpr Matrix3f sut;

        for (std::size_t i = 0; i <= 8; ++i)
        {
            EXPECT_FLOAT_EQ(sut[i], 0.0f);
        }
    }

    TEST(Matrix3fTests, constexprructor_ShouldSetElements_WhenProvidingValues)
    {
        constexpr float expectedM00 = 1.0f;
        constexpr float expectedM10 = 2.0f;
        constexpr float expectedM20 = 3.0f;

        constexpr float expectedM01 = 4.0f;
        constexpr float expectedM11 = 5.0f;
        constexpr float expectedM21 = 6.0f;

        constexpr float expectedM02 = 7.0f;
        constexpr float expectedM12 = 8.0f;
        constexpr float expectedM22 = 9.0f;

        constexpr Matrix3f sut(
            expectedM00, expectedM10, expectedM20,
            expectedM01, expectedM11, expectedM21,
            expectedM02, expectedM12, expectedM22
        );

        EXPECT_FLOAT_EQ(sut[0], expectedM00);
        EXPECT_FLOAT_EQ(sut[1], expectedM10);
        EXPECT_FLOAT_EQ(sut[2], expectedM20);

        EXPECT_FLOAT_EQ(sut[3], expectedM01);
        EXPECT_FLOAT_EQ(sut[4], expectedM11);
        EXPECT_FLOAT_EQ(sut[5], expectedM21);

        EXPECT_FLOAT_EQ(sut[6], expectedM02);
        EXPECT_FLOAT_EQ(sut[7], expectedM12);
        EXPECT_FLOAT_EQ(sut[8], expectedM22);
    }

    TEST(Matrix3fTests, AddOperator_ShouldReturnSum_WhenAddingTwoMatrices)
    {
        constexpr Matrix3f sut(
            2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f,
            8.0f, 9.0f, 10.0f
        );
        constexpr Matrix3f other(
            2.5f, 3.5f, 4.5f,
            5.5f, 6.5f, 7.5f,
            8.5f, 9.5f, 10.5f
        );

        constexpr Matrix3f result = sut + other;

        EXPECT_FLOAT_EQ(result[0], 4.5f);
        EXPECT_FLOAT_EQ(result[1], 6.5f);
        EXPECT_FLOAT_EQ(result[2], 8.5f);
        EXPECT_FLOAT_EQ(result[3], 10.5f);
        EXPECT_FLOAT_EQ(result[4], 12.5f);
        EXPECT_FLOAT_EQ(result[5], 14.5f);
        EXPECT_FLOAT_EQ(result[6], 16.5f);
        EXPECT_FLOAT_EQ(result[7], 18.5f);
        EXPECT_FLOAT_EQ(result[8], 20.5f);
    }

    TEST(Matrix3fTests, SubtractOperator_ShouldReturnDifference_WhenSubtractingTwoMatrics)
    {
        constexpr Matrix3f sut(
            2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f,
            8.0f, 9.0f, 10.0f
        );
        constexpr Matrix3f other(
            2.5f, 3.5f, 4.5f,
            5.5f, 6.5f, 7.5f,
            8.5f, 9.5f, 10.5f
        );

        constexpr Matrix3f result = sut - other;

        EXPECT_FLOAT_EQ(result[0], -0.5f);
        EXPECT_FLOAT_EQ(result[1], -0.5f);
        EXPECT_FLOAT_EQ(result[2], -0.5f);
        EXPECT_FLOAT_EQ(result[3], -0.5f);
        EXPECT_FLOAT_EQ(result[4], -0.5f);
        EXPECT_FLOAT_EQ(result[5], -0.5f);
        EXPECT_FLOAT_EQ(result[6], -0.5f);
        EXPECT_FLOAT_EQ(result[7], -0.5f);
        EXPECT_FLOAT_EQ(result[8], -0.5f);
    }

    TEST(Matrix3fTests, MultiplyOperator_ShouldScaleMatrix_WhenMultiplyingByScalar)
    {
        constexpr Matrix3f sut(
            2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f,
            8.0f, 9.0f, 10.0f
        );
        constexpr float scalar = 5.0f;

        constexpr Matrix3f result = sut * scalar;

        EXPECT_FLOAT_EQ(result[0], 10.0f);
        EXPECT_FLOAT_EQ(result[1], 15.0f);
        EXPECT_FLOAT_EQ(result[2], 20.0f);
        EXPECT_FLOAT_EQ(result[3], 25.0f);
        EXPECT_FLOAT_EQ(result[4], 30.0f);
        EXPECT_FLOAT_EQ(result[5], 35.0f);
        EXPECT_FLOAT_EQ(result[6], 40.0f);
        EXPECT_FLOAT_EQ(result[7], 45.0f);
        EXPECT_FLOAT_EQ(result[8], 50.0f);
    }

    TEST(Matrix3fTests, MultiplyOperator_ShouldReturnProduct_WhenMultiplyingTwoMatrices)
    {
        constexpr Matrix3f sut(
            2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f,
            8.0f, 9.0f, 10.0f
        );
        constexpr Matrix3f other(
            11.0f, 12.0f, 13.0f,
            14.0f, 15.0f, 16.0f,
            17.0f, 18.0f, 19.0f
        );

        constexpr Matrix3f result = sut * other;

        EXPECT_FLOAT_EQ(result[0], 186.0f);
        EXPECT_FLOAT_EQ(result[1], 222.0f);
        EXPECT_FLOAT_EQ(result[2], 258.0f);

        EXPECT_FLOAT_EQ(result[3], 231.0f);
        EXPECT_FLOAT_EQ(result[4], 276.0f);
        EXPECT_FLOAT_EQ(result[5], 321.0f);

        EXPECT_FLOAT_EQ(result[6], 276.0f);
        EXPECT_FLOAT_EQ(result[7], 330.0f);
        EXPECT_FLOAT_EQ(result[8], 384.0f);
    }

    TEST(Matrix3fTests, MultiplyOperator_ShouldReturnVectorProduct_WhenMultiplyingByVector)
    {
        constexpr Vector3f scale(3.0f, 2.0f, 1.0f);
        constexpr Matrix3f sut(
            2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f,
            8.0f, 9.0f, 10.0f
        );

        constexpr Vector3f result = sut * scale;

        EXPECT_FLOAT_EQ(result.X, 24.0f);
        EXPECT_FLOAT_EQ(result.Y, 30.0f);
        EXPECT_FLOAT_EQ(result.Z, 36.0f);
    }

    TEST(Matrix3fTests, Identity_ShouldReturnDefaults_WhenCalled)
    {
        constexpr Matrix3f result = Matrix3f::Identity();

        EXPECT_FLOAT_EQ(result[0], 1.0f);
        EXPECT_FLOAT_EQ(result[1], 0.0f);
        EXPECT_FLOAT_EQ(result[2], 0.0f);
        EXPECT_FLOAT_EQ(result[3], 0.0f);
        EXPECT_FLOAT_EQ(result[4], 1.0f);
        EXPECT_FLOAT_EQ(result[5], 0.0f);
        EXPECT_FLOAT_EQ(result[6], 0.0f);
        EXPECT_FLOAT_EQ(result[7], 0.0f);
        EXPECT_FLOAT_EQ(result[8], 1.0f);
    }

    TEST(Matrix3fTests, Scale_ShouldReturnScaleMatrix_WhenScaledByVector2f)
    {
        constexpr Vector2f scale(2.0f, 3.0f);

        constexpr Matrix3f result = Matrix3f::Scale(scale);

        EXPECT_FLOAT_EQ(result[0], scale.X);
        EXPECT_FLOAT_EQ(result[1], 0.0f);
        EXPECT_FLOAT_EQ(result[2], 0.0f);
        EXPECT_FLOAT_EQ(result[3], 0.0f);
        EXPECT_FLOAT_EQ(result[4], scale.Y);
        EXPECT_FLOAT_EQ(result[5], 0.0f);
        EXPECT_FLOAT_EQ(result[6], 0.0f);
        EXPECT_FLOAT_EQ(result[7], 0.0f);
        EXPECT_FLOAT_EQ(result[8], 1.0f);
    }

    TEST(Matrix3fTests, Scale_ShouldReturnScaleMatrix_WhenScaledByVector3f)
    {
        constexpr Vector3f scale(2.0f, 3.0f, 5.0f);

        constexpr Matrix3f result = Matrix3f::Scale(scale);

        EXPECT_FLOAT_EQ(result[0], scale.X);
        EXPECT_FLOAT_EQ(result[1], 0.0f);
        EXPECT_FLOAT_EQ(result[2], 0.0f);
        EXPECT_FLOAT_EQ(result[3], 0.0f);
        EXPECT_FLOAT_EQ(result[4], scale.Y);
        EXPECT_FLOAT_EQ(result[5], 0.0f);
        EXPECT_FLOAT_EQ(result[6], 0.0f);
        EXPECT_FLOAT_EQ(result[7], 0.0f);
        EXPECT_FLOAT_EQ(result[8], scale.Z);
    }

    TEST(Matrix3fTests, RotationX_ShouldRotateVectorCounterClockwise)
    {
        constexpr float angle = std::numbers::pi_v<float> / 2.0f;
        constexpr Vector3f vector(1.0f, 4.0f, 2.0f);

        const Matrix3f sut = Matrix3f::RotationX(angle);
        const Vector3f result = sut * vector;

        EXPECT_NEAR(result.X, 1.0f, 0.0001f);
        EXPECT_NEAR(result.Y, -2.0f, 0.0001f);
        EXPECT_NEAR(result.Z, 4.0f, 0.0001f);
    }

    TEST(Matrix3fTests, RotationY_ShouldRotateVectorCounterClockwise)
    {
        constexpr float angle = std::numbers::pi_v<float> / 2.0f;
        constexpr Vector3f vector(1.0f, 4.0f, 2.0f);

        const Matrix3f sut = Matrix3f::RotationY(angle);
        const Vector3f result = sut * vector;

        EXPECT_NEAR(result.X, 2.0f, 0.0001f);
        EXPECT_NEAR(result.Y, 4.0f, 0.0001f);
        EXPECT_NEAR(result.Z, -1.0f, 0.0001f);
    }

    TEST(Matrix3fTests, RotationZ_ShouldRotateVectorCounterClockwise)
    {
        constexpr float angle = std::numbers::pi_v<float> / 2.0f;
        constexpr Vector3f vector(1.0f, 4.0f, 2.0f);

        const Matrix3f sut = Matrix3f::RotationZ(angle);
        const Vector3f result = sut * vector;

        EXPECT_NEAR(result.X, -4.0f, 0.0001f);
        EXPECT_NEAR(result.Y, 1.0f, 0.0001f);
        EXPECT_NEAR(result.Z, 2.0f, 0.0001f);
    }

    TEST(Matrix3fTests, Translation_ShouldTranslatePointByVector2Amount)
    {
        constexpr Vector2f translationAmount(5.0f, 8.0f);
        constexpr Vector3f point(2.0f, 3.0f, 1.0f);

        constexpr Matrix3f translation = Matrix3f::Translation(translationAmount);
        constexpr Vector3f result = translation * point;

        EXPECT_FLOAT_EQ(result.X, 7.0f);
        EXPECT_FLOAT_EQ(result.Y, 11.0f);
        EXPECT_FLOAT_EQ(result.Z, 1.0f);
    }
}