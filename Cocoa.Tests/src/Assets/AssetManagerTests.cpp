#include <Assets/AssetManager.hpp>
#include <Assets/Image.hpp>

#include <gtest/gtest.h>
#include <filesystem>
#include <string>

namespace Cocoa::Assets::Tests
{
	TEST(AssetManagerTests, LoadImage_ShouldReturnImage_WhenProvidingPath)
	{
		const std::filesystem::path rootPath = "TestData/Resources";
		AssetManager sut(rootPath);

		const Image& result = sut.LoadImage("Images/test.png");

		EXPECT_NE(&result, nullptr);
	}

	TEST(AssetManagerTests, LoadImage_ShouldReturnSameImage_WhenProvidingSameImagePath)
	{
		const std::filesystem::path rootPath = "TestData/Resources";
		AssetManager sut(rootPath);

		const Image& result1 = sut.LoadImage("Images/test.png");
		const Image& result2 = sut.LoadImage("Images/test.png");

		EXPECT_EQ(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadImage_ShouldReturnDifferentImage_WhenProvidingDifferentImagePath)
	{
		const std::filesystem::path rootPath = "TestData/Resources";
		AssetManager sut(rootPath);

		const Image& result1 = sut.LoadImage("Images/test.png");
		const Image& result2 = sut.LoadImage("Images/test2.png");

		EXPECT_NE(&result1, &result2);
	}
}