#include <Platforms/WindowProperties.hpp>

#include <gtest/gtest.h>
#include <string>

namespace Cocoa::Platforms::Tests
{
    TEST(WindowPropertiesTests, GetWidth_ShouldReturnConstructorWidth_WhenCreated)
    {
        constexpr uint32_t expectedWidth = 1280;
        constexpr uint32_t height = 720;
        const std::string title = "Vexxus";

        const Platforms::WindowProperties sut(expectedWidth, height, title);

        EXPECT_EQ(expectedWidth, sut.GetWidth());
    }

    TEST(WindowPropertiesTests, GetHeight_ShouldReturnConstructorHeight_WhenCreated)
    {
        constexpr uint32_t width = 1280;
        constexpr uint32_t expectedHeight = 720;
        const std::string title = "Vexxus";

        const Platforms::WindowProperties sut(width, expectedHeight, title);

        EXPECT_EQ(expectedHeight, sut.GetHeight());
    }

    TEST(WindowPropertiesTests, GetTitle_ShouldReturnConstructorTitle_WhenCreated)
    {
        constexpr uint32_t width = 1280;
        constexpr uint32_t height = 720;
        const std::string expectedTitle = "Vexxus";

        const Platforms::WindowProperties sut(width, height, expectedTitle);

        EXPECT_EQ(expectedTitle, sut.GetTitle());
    }

    TEST(WindowPropertiesTests, GetTitle_ShouldStoreOwnTitleCopy_WhenSourceStringIsModified)
    {
        constexpr uint32_t width = 1280;
        constexpr uint32_t height = 720;
        std::string title = "Vexxus";

        const Platforms::WindowProperties sut(width, height, title);
        title = "Changed Title";

        EXPECT_EQ("Vexxus", sut.GetTitle());
    }

    TEST(WindowPropertiesTests, Constructor_ShouldMoveTitle_WhenRvalueStringIsProvided)
    {
        constexpr uint32_t width = 1280;
        constexpr uint32_t height = 720;

        const Platforms::WindowProperties sut(width, height, std::string("Vexxus"));

        EXPECT_EQ("Vexxus", sut.GetTitle());
    }
}