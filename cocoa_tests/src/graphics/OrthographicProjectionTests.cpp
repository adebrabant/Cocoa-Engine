#include <graphics/OrthographicProjection.hpp>
#include <gtest/gtest.h>
#include <math/Matrix4f.hpp>
#include <math/Vector3f.hpp>

namespace cocoa_tests::graphics
{
    TEST(OrthographicProjectionTests, Constructor_ShouldCreateProjectionMatrix_WhenGivenValidBounds)
    {
        constexpr float aspectRatio = 800.0f / 600.0f;
        const cocoa::graphics::OrthographicProjection sut(
            -aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        const cocoa::math::Matrix4f result = sut.getProjectionMatrix();

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
        constexpr cocoa::math::Vector3f expectedPosition = cocoa::math::Vector3f(2.0f, 1.5f, 1.0f);
        constexpr float aspectRatio = 800.0f / 600.0f;
        cocoa::graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        sut.setPosition(expectedPosition);
        const cocoa::math::Vector3f result = sut.getPosition();

        ASSERT_FLOAT_EQ(result.x, expectedPosition.x);
        ASSERT_FLOAT_EQ(result.y, expectedPosition.y);
        ASSERT_FLOAT_EQ(result.z, expectedPosition.z);
    }

    TEST(OrthographicProjectionTests, GetPosition_ShouldReturnVector3_WhenCalled)
    {
        constexpr float aspectRatio = 800.0f / 600.0f;
        const cocoa::graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        const cocoa::math::Vector3f result = sut.getPosition();

        ASSERT_FLOAT_EQ(result.x, 0.0f);
        ASSERT_FLOAT_EQ(result.y, 0.0f);
        ASSERT_FLOAT_EQ(result.z, 0.0f);
    }

    TEST(OrthographicProjectionTests, GetViewProjectionMatrix_ShouldReturnProjectionMatrixTimesViewMatrix_WhenCalled)
    {
        constexpr float aspectRatio = 800.0f / 600.0f;
        cocoa::graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
        sut.setPosition({ 5.0f, 2.0f, 3.0f});
        sut.setRotation(1.5f);

        const cocoa::math::Matrix4f result = sut.getViewProjectionMatrix();

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
        cocoa::graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        sut.setProjection(
            -3.0f, 5.0f,
            -2.0f, 6.0f,
            1.0f, 9.0f
        );

        const cocoa::math::Matrix4f result = sut.getProjectionMatrix();

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
        cocoa::graphics::OrthographicProjection sut(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

        sut.setRotation(expectedRotation);
        const float result = sut.getRotation();

        ASSERT_FLOAT_EQ(result, expectedRotation);
    }
}
