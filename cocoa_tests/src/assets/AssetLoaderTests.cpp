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

        const std::string result = sut.loadText(path);

        EXPECT_EQ(result, "Hello from AssetLoader test.");
    }

    TEST(AssetLoaderTests, LoadText_ShouldReturnContents_WhenBytesExist)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "test_data/resources/texts/sample.txt");

        const std::string result = sut.loadText(bytes);

        EXPECT_EQ(result, "Hello from AssetLoader test.");
    }

    TEST(AssetLoaderTests, LoadText_ShouldReturnEmptyContents_WhenBytesAreEmpty)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes;

        const std::string result = sut.loadText(bytes);

        EXPECT_EQ(result, "");
    }

    TEST(AssetLoaderTests, LoadText_ShouldThrowError_WhenFileDoesNotExist)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/texts/missing.txt";

        EXPECT_THROW(
            {
                auto value = sut.loadText(path);
            },
            std::runtime_error
        );
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnImage_WhenFileExists)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/images/test.png";

        const cocoa::assets::Image result = sut.loadImage(path);

        EXPECT_GT(result.width, 0);
        EXPECT_GT(result.height, 0);
        EXPECT_EQ(result.channels, 4);
        EXPECT_FALSE(result.pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnEmptyImage_WhenFileDoesNotExist)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/images/missing.png";

        const cocoa::assets::Image result = sut.loadImage(path);

        EXPECT_EQ(result.width, 0);
        EXPECT_EQ(result.height, 0);
        EXPECT_EQ(result.channels, 4);
        EXPECT_TRUE(result.pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldSetPixelSize_WhenFileExists)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/images/test.png";

        const cocoa::assets::Image result = sut.loadImage(path);

        const size_t expectedSize =
            static_cast<size_t>(result.width) *
            static_cast<size_t>(result.height) *
            4;

        EXPECT_EQ(result.pixels.size(), expectedSize);
    }

    TEST(AssetLoaderTests, LoadImage_ShouldForceFourChannels_WhenLoadingImage)
    {
        cocoa::assets::AssetLoader sut;
        const std::filesystem::path path =
            "test_data/resources/images/test.png";

        const cocoa::assets::Image result = sut.loadImage(path);

        EXPECT_EQ(result.channels, 4);
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnImage_WhenBytesExist)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "test_data/resources/images/test.png");

        const cocoa::assets::Image result = sut.loadImage(bytes);

        EXPECT_GT(result.width, 0);
        EXPECT_GT(result.height, 0);
        EXPECT_EQ(result.channels, 4);
        EXPECT_FALSE(result.pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldReturnEmptyImage_WhenBytesAreEmpty)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes;

        const cocoa::assets::Image result = sut.loadImage(bytes);

        EXPECT_EQ(result.width, 0);
        EXPECT_EQ(result.height, 0);
        EXPECT_EQ(result.channels, 4);
        EXPECT_TRUE(result.pixels.empty());
    }

    TEST(AssetLoaderTests, LoadImage_ShouldSetPixelSize_WhenBytesExist)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "test_data/resources/images/test.png");

        const cocoa::assets::Image result = sut.loadImage(bytes);

        const size_t expectedSize =
            static_cast<size_t>(result.width) *
            static_cast<size_t>(result.height) *
            4;

        EXPECT_EQ(result.pixels.size(), expectedSize);
    }

    TEST(AssetLoaderTests, LoadImage_ShouldForceFourChannels_WhenLoadingImageFromBytes)
    {
        cocoa::assets::AssetLoader sut;
        std::vector<std::byte> bytes = Helpers::ReadFileBytes(
            "test_data/resources/images/test.png");

        const cocoa::assets::Image result = sut.loadImage(bytes);

        EXPECT_EQ(result.channels, 4);
    }
}
