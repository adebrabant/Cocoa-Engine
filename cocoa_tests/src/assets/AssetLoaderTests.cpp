#include "helpers/TestFileReader.hpp"
#include <assets/AssetLoader.hpp>
#include <assets/Image.hpp>

#include <gtest/gtest.h>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace CocoaTests::Assets
{
    TEST(AssetLoaderTests, LoadText_ShouldReturnContents_WhenFileExists)
    {
        cocoa::Assets::AssetLoader sut;
        const std::filesystem::path path =
            "TestData/Resources/Texts/sample.txt";

        const std::string result = sut.LoadText(path);

        EXPECT_EQ(result, "Hello from AssetLoader test.");
    }

    TEST(AssetLoaderTests, LoadText_ShouldReturnContents_WhenBytesExist)
    {
        cocoa::Assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "TestData/Resources/Texts/sample.txt");

        const std::string result = sut.LoadText(bytes);

        EXPECT_EQ(result, "Hello from AssetLoader test.");
    }

    TEST(AssetLoaderTests, LoadText_ShouldReturnEmptyContents_WhenBytesAreEmpty)
    {
        cocoa::Assets::AssetLoader sut;
        std::vector<std::byte> bytes;

        const std::string result = sut.LoadText(bytes);

        EXPECT_EQ(result, "");
    }

    TEST(AssetLoaderTests, LoadText_ShouldThrowError_WhenFileDoesNotExist)
    {
        cocoa::Assets::AssetLoader sut;
        const std::filesystem::path path =
            "TestData/Resources/Texts/missing.txt";

        EXPECT_THROW(
            {
                auto value = sut.LoadText(path);
            },
            std::runtime_error
        );
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnImage_WhenFileExists)
    {
        cocoa::Assets::AssetLoader sut;
        const std::filesystem::path path =
            "TestData/Resources/Images/test.png";

        const cocoa::Assets::Image result = sut.LoadImage(path);

        EXPECT_GT(result.Width, 0);
        EXPECT_GT(result.Height, 0);
        EXPECT_EQ(result.Channels, 4);
        EXPECT_FALSE(result.Pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnEmptyImage_WhenFileDoesNotExist)
    {
        cocoa::Assets::AssetLoader sut;
        const std::filesystem::path path =
            "TestData/Resources/Images/missing.png";

        const cocoa::Assets::Image result = sut.LoadImage(path);

        EXPECT_EQ(result.Width, 0);
        EXPECT_EQ(result.Height, 0);
        EXPECT_EQ(result.Channels, 4);
        EXPECT_TRUE(result.Pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldSetPixelSize_WhenFileExists)
    {
        cocoa::Assets::AssetLoader sut;
        const std::filesystem::path path =
            "TestData/Resources/Images/test.png";

        const cocoa::Assets::Image result = sut.LoadImage(path);

        const size_t expectedSize =
            static_cast<size_t>(result.Width) *
            static_cast<size_t>(result.Height) *
            4;

        EXPECT_EQ(result.Pixels.size(), expectedSize);
    }

    TEST(AssetLoaderTests, LoadImage_ShouldForceFourChannels_WhenLoadingImage)
    {
        cocoa::Assets::AssetLoader sut;
        const std::filesystem::path path =
            "TestData/Resources/Images/test.png";

        const cocoa::Assets::Image result = sut.LoadImage(path);

        EXPECT_EQ(result.Channels, 4);
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnImage_WhenBytesExist)
    {
        cocoa::Assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "TestData/Resources/Images/test.png");

        const cocoa::Assets::Image result = sut.LoadImage(bytes);

        EXPECT_GT(result.Width, 0);
        EXPECT_GT(result.Height, 0);
        EXPECT_EQ(result.Channels, 4);
        EXPECT_FALSE(result.Pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnEmptyImage_WhenBytesAreEmpty)
    {
        cocoa::Assets::AssetLoader sut;
        std::vector<std::byte> bytes;

        const cocoa::Assets::Image result = sut.LoadImage(bytes);

        EXPECT_EQ(result.Width, 0);
        EXPECT_EQ(result.Height, 0);
        EXPECT_EQ(result.Channels, 4);
        EXPECT_TRUE(result.Pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldSetPixelSize_WhenBytesExist)
    {
        cocoa::Assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "TestData/Resources/Images/test.png");

        const cocoa::Assets::Image result = sut.LoadImage(bytes);

        const size_t expectedSize =
            static_cast<size_t>(result.Width) *
            static_cast<size_t>(result.Height) *
            4;

        EXPECT_EQ(result.Pixels.size(), expectedSize);
    }

    TEST(AssetLoaderTests, LoadImage_ShouldForceFourChannels_WhenLoadingImageFromBytes)
    {
        cocoa::Assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "TestData/Resources/Images/test.png");

        const cocoa::Assets::Image result = sut.LoadImage(bytes);

        EXPECT_EQ(result.Channels, 4);
    }
}