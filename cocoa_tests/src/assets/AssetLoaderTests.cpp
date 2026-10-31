#include "helpers/TestFileReader.hpp"
#include <assets/AssetLoader.hpp>
#include <assets/Image.hpp>

#include <gtest/gtest.h>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace cocoa_tests::assets
{
    TEST(AssetLoaderTests, LoadText_ShouldReturnContents_WhenFileExists)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/texts/sample.txt";

        const std::string result = sut.LoadText(path);

        EXPECT_EQ(result, "Hello from AssetLoader test.");
    }

    TEST(AssetLoaderTests, LoadText_ShouldReturnContents_WhenBytesExist)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "test_data/resources/texts/sample.txt");

        const std::string result = sut.LoadText(bytes);

        EXPECT_EQ(result, "Hello from AssetLoader test.");
    }

    TEST(AssetLoaderTests, LoadText_ShouldReturnEmptyContents_WhenBytesAreEmpty)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes;

        const std::string result = sut.LoadText(bytes);

        EXPECT_EQ(result, "");
    }

    TEST(AssetLoaderTests, LoadText_ShouldThrowError_WhenFileDoesNotExist)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/texts/missing.txt";

        EXPECT_THROW(
            {
                auto value = sut.LoadText(path);
            },
            std::runtime_error
        );
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnImage_WhenFileExists)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/images/test.png";

        const cocoa::assets::Image result = sut.LoadImage(path);

        EXPECT_GT(result.Width, 0);
        EXPECT_GT(result.Height, 0);
        EXPECT_EQ(result.Channels, 4);
        EXPECT_FALSE(result.Pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnEmptyImage_WhenFileDoesNotExist)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/images/missing.png";

        const cocoa::assets::Image result = sut.LoadImage(path);

        EXPECT_EQ(result.Width, 0);
        EXPECT_EQ(result.Height, 0);
        EXPECT_EQ(result.Channels, 4);
        EXPECT_TRUE(result.Pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldSetPixelSize_WhenFileExists)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/images/test.png";

        const cocoa::assets::Image result = sut.LoadImage(path);

        const size_t expectedSize =
            static_cast<size_t>(result.Width) *
            static_cast<size_t>(result.Height) *
            4;

        EXPECT_EQ(result.Pixels.size(), expectedSize);
    }

    TEST(AssetLoaderTests, LoadImage_ShouldForceFourChannels_WhenLoadingImage)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/images/test.png";

        const cocoa::assets::Image result = sut.LoadImage(path);

        EXPECT_EQ(result.Channels, 4);
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnImage_WhenBytesExist)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "test_data/resources/images/test.png");

        const cocoa::assets::Image result = sut.LoadImage(bytes);

        EXPECT_GT(result.Width, 0);
        EXPECT_GT(result.Height, 0);
        EXPECT_EQ(result.Channels, 4);
        EXPECT_FALSE(result.Pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnEmptyImage_WhenBytesAreEmpty)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes;

        const cocoa::assets::Image result = sut.LoadImage(bytes);

        EXPECT_EQ(result.Width, 0);
        EXPECT_EQ(result.Height, 0);
        EXPECT_EQ(result.Channels, 4);
        EXPECT_TRUE(result.Pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldSetPixelSize_WhenBytesExist)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "test_data/resources/images/test.png");

        const cocoa::assets::Image result = sut.LoadImage(bytes);

        const size_t expectedSize =
            static_cast<size_t>(result.Width) *
            static_cast<size_t>(result.Height) *
            4;

        EXPECT_EQ(result.Pixels.size(), expectedSize);
    }

    TEST(AssetLoaderTests, LoadImage_ShouldForceFourChannels_WhenLoadingImageFromBytes)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "test_data/resources/images/test.png");

        const cocoa::assets::Image result = sut.LoadImage(bytes);

        EXPECT_EQ(result.Channels, 4);
    }
}
