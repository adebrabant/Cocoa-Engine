#include <Scenes/SceneCamera.hpp>
#include <Graphics/Viewport.hpp>
#include <Math/Matrix4f.hpp>
#include <gtest/gtest.h>

namespace CocoaTests::Scenes
{
    TEST(SceneCameraTests, GetViewProjectionMatrix_ShouldReturnUpdatedMatrix_WhenViewportWidthChanges)
    {
        Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
        Cocoa::Scenes::SceneCamera sut(viewport);

        const Cocoa::Math::Matrix4f resultBefore = sut.GetViewProjectionMatrix();
        viewport.Resize(0, 0, 1920, 600);
        const Cocoa::Math::Matrix4f resultAfter = sut.GetViewProjectionMatrix();

        EXPECT_NE(resultBefore[0], resultAfter[0]);
    }

    TEST(SceneCameraTests, GetViewProjectionMatrix_ShouldReturnUpdatedMatrix_WhenViewportHeightChanges)
    {
        Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
        Cocoa::Scenes::SceneCamera sut(viewport);

        const Cocoa::Math::Matrix4f resultBefore = sut.GetViewProjectionMatrix();
        viewport.Resize(0, 0, 800, 400);
        const Cocoa::Math::Matrix4f resultAfter = sut.GetViewProjectionMatrix();

        EXPECT_NE(resultBefore[0], resultAfter[0]);
    }

    TEST(SceneCameraTests, GetViewProjectionMatrix_ShouldNotChange_WhenOnlyViewportPositionChanges)
    {
        Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
        Cocoa::Scenes::SceneCamera sut(viewport);

        const Cocoa::Math::Matrix4f resultBefore = sut.GetViewProjectionMatrix();
        viewport.Resize(100, 100, 800, 600);
        const Cocoa::Math::Matrix4f resultAfter = sut.GetViewProjectionMatrix();

        EXPECT_EQ(resultBefore[0], resultAfter[0]);
    }
}