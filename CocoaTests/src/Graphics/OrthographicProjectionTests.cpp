#include <Graphics/OrthographicProjection.hpp>
#include <Math/Matrix4f.hpp>
#include <Math/Vector3f.hpp>
#include <gtest/gtest.h>

namespace CocoaTests::Graphics
{
    TEST(OrthographicProjectionTests, Constructor_ShouldCreateProjectionMatrix_WhenGivenValidBounds)
    {
        constexpr float aspectRatio = 800.0f / 600.0f;
        const Cocoa::Graphics::OrthographicProjection sut(
            -aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        const Cocoa::Math::Matrix4f result = sut.GetProjectionMatrix();

        EXPECT_FLOAT_EQ(result[0], 0.75f);
        EXPECT_FLOAT_EQ(result[1], 0.0f);
        EXPECT_FLOAT_EQ(result[2], 0.0f);
        EXPECT_FLOAT_EQ(result[3], 0.0f);
        EXPECT_FLOAT_EQ(result[4], 0.0f);
        EXPECT_FLOAT_EQ(result[5], 1.0f);
        EXPECT_FLOAT_EQ(result[6], 0.0f);
        EXPECT_FLOAT_EQ(result[7], 0.0f);
        EXPECT_FLOAT_EQ(result[8], 0.0f);
        EXPECT_FLOAT_EQ(result[9], 0.0f);
        EXPECT_FLOAT_EQ(result[10], -1.0f);
        EXPECT_FLOAT_EQ(result[11], 0.0f);
        EXPECT_FLOAT_EQ(result[12], 0.0f);
        EXPECT_FLOAT_EQ(result[13], 0.0f);
        EXPECT_FLOAT_EQ(result[14], 0.0f);
        EXPECT_FLOAT_EQ(result[15], 1.0f);
    }

    TEST(OrthographicProjectionTests, SetPosition_ShouldSetCamerasPosition_WhenGivenVector3)
    {
        constexpr Cocoa::Math::Vector3f expectedPosition = Cocoa::Math::Vector3f(2.0f, 1.5f, 1.0f);
        constexpr float aspectRatio = 800.0f / 600.0f;
        Cocoa::Graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        sut.SetPosition(expectedPosition);
        const Cocoa::Math::Vector3f result = sut.GetPosition();

        ASSERT_FLOAT_EQ(result.X, expectedPosition.X);
        ASSERT_FLOAT_EQ(result.Y, expectedPosition.Y);
        ASSERT_FLOAT_EQ(result.Z, expectedPosition.Z);
    }

    TEST(OrthographicProjectionTests, GetPosition_ShouldReturnVector3_WhenCalled)
    {
        constexpr float aspectRatio = 800.0f / 600.0f;
        const Cocoa::Graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        const Cocoa::Math::Vector3f result = sut.GetPosition();

        ASSERT_FLOAT_EQ(result.X, 0.0f);
        ASSERT_FLOAT_EQ(result.Y, 0.0f);
        ASSERT_FLOAT_EQ(result.Z, 0.0f);
    }

    TEST(OrthographicProjectionTests, GetViewProjectionMatrix_ShouldReturnProjectionMatrixTimesViewMatrix_WhenCalled)
    {
        constexpr float aspectRatio = 800.0f / 600.0f;
        Cocoa::Graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
        sut.SetPosition({ 5.0f, 2.0f, 3.0f});
        sut.SetRotation(1.5f);

        const Cocoa::Math::Matrix4f result = sut.GetViewProjectionMatrix();

        EXPECT_FLOAT_EQ(result[0], 0.053052898f);
        EXPECT_FLOAT_EQ(result[1], -0.997495f);
        EXPECT_FLOAT_EQ(result[2], 0.0f);
        EXPECT_FLOAT_EQ(result[3], 0.0f);
        EXPECT_FLOAT_EQ(result[4], 0.74812126f);
        EXPECT_FLOAT_EQ(result[5], 0.070737198f);
        EXPECT_FLOAT_EQ(result[6], 0.0f);
        EXPECT_FLOAT_EQ(result[7], 0.0f);
        EXPECT_FLOAT_EQ(result[8], 0.0f);
        EXPECT_FLOAT_EQ(result[9], 0.0f);
        EXPECT_FLOAT_EQ(result[10], -1.0f);
        EXPECT_FLOAT_EQ(result[11], 0.0f);
        EXPECT_FLOAT_EQ(result[12], -1.761507f);
        EXPECT_FLOAT_EQ(result[13], 4.8460007f);
        EXPECT_FLOAT_EQ(result[14], 3.0000002f);
        EXPECT_FLOAT_EQ(result[15], 1.0f);
    }

    TEST(OrthographicProjectionTests, SetProjection_ShouldSetOrthoProjectMatrix_WhenGivenValidInput)
    {
        constexpr float aspectRatio = 800.0f / 600.0f;
        Cocoa::Graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        sut.SetProjection(
            -3.0f, 5.0f,
            -2.0f, 6.0f,
            1.0f, 9.0f
        );

        const Cocoa::Math::Matrix4f result = sut.GetProjectionMatrix();

        EXPECT_FLOAT_EQ(result[0], 0.25f);
        EXPECT_FLOAT_EQ(result[1], 0.0f);
        EXPECT_FLOAT_EQ(result[2], 0.0f);
        EXPECT_FLOAT_EQ(result[3], 0.0f);

        EXPECT_FLOAT_EQ(result[4], 0.0f);
        EXPECT_FLOAT_EQ(result[5], 0.25f);
        EXPECT_FLOAT_EQ(result[6], 0.0f);
        EXPECT_FLOAT_EQ(result[7], 0.0f);

        EXPECT_FLOAT_EQ(result[8], 0.0f);
        EXPECT_FLOAT_EQ(result[9], 0.0f);
        EXPECT_FLOAT_EQ(result[10], -0.25f);
        EXPECT_FLOAT_EQ(result[11], 0.0f);

        EXPECT_FLOAT_EQ(result[12], -0.25f);
        EXPECT_FLOAT_EQ(result[13], -0.5f);
        EXPECT_FLOAT_EQ(result[14], -1.25f);
        EXPECT_FLOAT_EQ(result[15], 1.0f);
    }

    TEST(OrthographicProjectionTests, SetRotation_ShouldSetCameraRotation_WhenGivenValidInput)
    {
        constexpr float expectedRotation = 5.0f;
        constexpr float aspectRatio = 800.0f / 600.0f;
        Cocoa::Graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        sut.SetRotation(expectedRotation);
        const float result = sut.GetRotation();

        ASSERT_FLOAT_EQ(result, expectedRotation);
    }
}