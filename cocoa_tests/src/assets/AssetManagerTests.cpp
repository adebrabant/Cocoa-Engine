#include "helpers/TestFileReader.hpp"
#include <assets/AssetManager.hpp>
#include <assets/Image.hpp>
#include <assets/ShaderSource.hpp>

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <filesystem>

namespace cocoa_tests::assets
{
	TEST(AssetManagerTests, LoadImage_ShouldReturnImage_WhenProvidingPath)
	{
		cocoa::assets::AssetManager sut;
		const std::filesystem::path path = "test_data/resources/images/test.png";
		const std::vector<std::byte> bytes = Helpers::ReadFileBytes(path);

		const cocoa::assets::Image& result = sut.loadImage(path.string(), bytes);

		EXPECT_NE(&result, nullptr);
	}

	TEST(AssetManagerTests, LoadImage_ShouldReturnSameImage_WhenProvidingSameImagePath)
	{
		cocoa::assets::AssetManager sut;
		const std::string imagePath = "images/test.png";
		const std::filesystem::path rootPath = "test_data/resources/";
		const std::vector<std::byte> bytes = Helpers::ReadFileBytes(rootPath / imagePath);

		const cocoa::assets::Image& result1 = sut.loadImage(imagePath, bytes);
		const cocoa::assets::Image& result2 = sut.loadImage(imagePath, bytes);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadImage_ShouldReturnDifferentImage_WhenProvidingDifferentImagePath)
	{
		cocoa::assets::AssetManager sut;
		const std::string testImagePath = "images/test.png";
		const std::string testImage2Path = "images/test2.png";
		const std::filesystem::path rootPath = "test_data/resources";
		const std::vector<std::byte> testImageBytes = Helpers::ReadFileBytes(rootPath / testImagePath);
		const std::vector<std::byte> testImage2Bytes = Helpers::ReadFileBytes(rootPath / testImage2Path);

		const cocoa::assets::Image& result1 = sut.loadImage(testImagePath, testImageBytes);
		const cocoa::assets::Image& result2 = sut.loadImage(testImage2Path, testImage2Bytes);

		EXPECT_NE(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadShader_ShouldReturnShaderSource_WhenProvidingPaths)
	{
		cocoa::assets::AssetManager sut;
		const std::string shaderId = "test-id";
		const std::string vertexPath = "texts/sample.txt";
		const std::string fragmentPath = "texts/sample2.txt";
		const std::filesystem::path rootPath = "test_data/resources";
		const std::vector<std::byte> vertexBytes = Helpers::ReadFileBytes(rootPath / vertexPath);
		const std::vector<std::byte> fragmentBytes = Helpers::ReadFileBytes(rootPath / fragmentPath);

		const cocoa::assets::ShaderSource& result = sut.loadShader(shaderId, vertexBytes, fragmentBytes);

		EXPECT_NE(&result, nullptr);
	}

	TEST(AssetManagerTests, LoadShader_ShouldReturnSameShaderSource_WhenProvidingSameShaderId)
	{
		cocoa::assets::AssetManager sut;
		const std::string shaderId = "test-id";
		const std::string vertexPath = "texts/sample.txt";
		const std::string fragmentPath = "texts/sample2.txt";
		const std::filesystem::path rootPath = "test_data/resources";
		const std::vector<std::byte> vertexBytes = Helpers::ReadFileBytes(rootPath / vertexPath);
		const std::vector<std::byte> fragmentBytes = Helpers::ReadFileBytes(rootPath / fragmentPath);

		const cocoa::assets::ShaderSource& result1 = sut.loadShader(shaderId, vertexBytes, fragmentBytes);
		const cocoa::assets::ShaderSource& result2 = sut.loadShader(shaderId, vertexBytes, fragmentBytes);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadShader_ShouldReturnDifferentShaderSource_WhenProvidingDifferentShaderId)
	{
		cocoa::assets::AssetManager sut;
		const std::string vertexPath = "texts/sample.txt";
		const std::string fragmentPath = "texts/sample2.txt";
		const std::filesystem::path rootPath = "test_data/resources";
		const std::vector<std::byte> vertexBytes = Helpers::ReadFileBytes(rootPath / vertexPath);
		const std::vector<std::byte> fragmentBytes = Helpers::ReadFileBytes(rootPath / fragmentPath);

		const cocoa::assets::ShaderSource& result1 = sut.loadShader("test-id", vertexBytes, fragmentBytes);
		const cocoa::assets::ShaderSource& result2 = sut.loadShader("some-id", vertexBytes, fragmentBytes);

		EXPECT_NE(&result1, &result2);
	}
}
