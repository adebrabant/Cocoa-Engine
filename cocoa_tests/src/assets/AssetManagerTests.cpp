#include "helpers/TestFileReader.hpp"
#include <assets/AssetManager.hpp>
#include <assets/Image.hpp>
#include <assets/ShaderSource.hpp>

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <filesystem>

namespace CocoaTests::Assets
{
	TEST(AssetManagerTests, LoadImage_ShouldReturnImage_WhenProvidingPath)
	{
		cocoa::Assets::AssetManager sut;
		const std::filesystem::path path = "TestData/Resources/Images/test.png";
		const std::vector<std::byte> bytes = Helpers::ReadFileBytes(path);

		const cocoa::Assets::Image& result = sut.LoadImage(path.string(), bytes);

		EXPECT_NE(&result, nullptr);
	}

	TEST(AssetManagerTests, LoadImage_ShouldReturnSameImage_WhenProvidingSameImagePath)
	{
		cocoa::Assets::AssetManager sut;
		const std::string imagePath = "Images/test.png";
		const std::filesystem::path rootPath = "TestData/Resources/";
		const std::vector<std::byte> bytes = Helpers::ReadFileBytes(rootPath / imagePath);

		const cocoa::Assets::Image& result1 = sut.LoadImage(imagePath, bytes);
		const cocoa::Assets::Image& result2 = sut.LoadImage(imagePath, bytes);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadImage_ShouldReturnDifferentImage_WhenProvidingDifferentImagePath)
	{
		cocoa::Assets::AssetManager sut;
		const std::string testImagePath = "Images/test.png";
		const std::string testImage2Path = "Images/test2.png";
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::vector<std::byte> testImageBytes = Helpers::ReadFileBytes(rootPath / testImagePath);
		const std::vector<std::byte> testImage2Bytes = Helpers::ReadFileBytes(rootPath / testImage2Path);

		const cocoa::Assets::Image& result1 = sut.LoadImage(testImagePath, testImageBytes);
		const cocoa::Assets::Image& result2 = sut.LoadImage(testImage2Path, testImage2Bytes);

		EXPECT_NE(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadShader_ShouldReturnShaderSource_WhenProvidingPaths)
	{
		cocoa::Assets::AssetManager sut;
		const std::string shaderId = "test-id";
		const std::string vertexPath = "Texts/sample.txt";
		const std::string fragmentPath = "Texts/sample2.txt";
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::vector<std::byte> vertexBytes = Helpers::ReadFileBytes(rootPath / vertexPath);
		const std::vector<std::byte> fragmentBytes = Helpers::ReadFileBytes(rootPath / fragmentPath);

		const cocoa::Assets::ShaderSource& result = sut.LoadShader(shaderId, vertexBytes, fragmentBytes);

		EXPECT_NE(&result, nullptr);
	}

	TEST(AssetManagerTests, LoadShader_ShouldReturnSameShaderSource_WhenProvidingSameShaderId)
	{
		cocoa::Assets::AssetManager sut;
		const std::string shaderId = "test-id";
		const std::string vertexPath = "Texts/sample.txt";
		const std::string fragmentPath = "Texts/sample2.txt";
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::vector<std::byte> vertexBytes = Helpers::ReadFileBytes(rootPath / vertexPath);
		const std::vector<std::byte> fragmentBytes = Helpers::ReadFileBytes(rootPath / fragmentPath);

		const cocoa::Assets::ShaderSource& result1 = sut.LoadShader(shaderId, vertexBytes, fragmentBytes);
		const cocoa::Assets::ShaderSource& result2 = sut.LoadShader(shaderId, vertexBytes, fragmentBytes);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadShader_ShouldReturnDifferentShaderSource_WhenProvidingDifferentShaderId)
	{
		cocoa::Assets::AssetManager sut;
		const std::string vertexPath = "Texts/sample.txt";
		const std::string fragmentPath = "Texts/sample2.txt";
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::vector<std::byte> vertexBytes = Helpers::ReadFileBytes(rootPath / vertexPath);
		const std::vector<std::byte> fragmentBytes = Helpers::ReadFileBytes(rootPath / fragmentPath);

		const cocoa::Assets::ShaderSource& result1 = sut.LoadShader("test-id", vertexBytes, fragmentBytes);
		const cocoa::Assets::ShaderSource& result2 = sut.LoadShader("some-id", vertexBytes, fragmentBytes);

		EXPECT_NE(&result1, &result2);
	}
}