#include <Assets/AssetManager.hpp>
#include <Assets/ShaderSource.hpp>
#include <Assets/Image.hpp>
#include "Helpers/TestFileReader.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <filesystem>

namespace CocoaTests::Assets
{
	TEST(AssetManagerTests, LoadImage_ShouldReturnImage_WhenProvidingPath)
	{
		Cocoa::Assets::AssetManager sut;
		const std::filesystem::path path = "TestData/Resources/Images/test.png";
		const std::vector<std::byte> bytes = Helpers::ReadFileBytes(path);

		const Cocoa::Assets::Image& result = sut.LoadImage(path.string(), bytes);

		EXPECT_NE(&result, nullptr);
	}

	TEST(AssetManagerTests, LoadImage_ShouldReturnSameImage_WhenProvidingSameImagePath)
	{
		Cocoa::Assets::AssetManager sut;
		const std::string imagePath = "Images/test.png";
		const std::filesystem::path rootPath = "TestData/Resources/";
		const std::vector<std::byte> bytes = Helpers::ReadFileBytes(rootPath / imagePath);

		const Cocoa::Assets::Image& result1 = sut.LoadImage(imagePath, bytes);
		const Cocoa::Assets::Image& result2 = sut.LoadImage(imagePath, bytes);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadImage_ShouldReturnDifferentImage_WhenProvidingDifferentImagePath)
	{
		Cocoa::Assets::AssetManager sut;
		const std::string testImagePath = "Images/test.png";
		const std::string testImage2Path = "Images/test2.png";
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::vector<std::byte> testImageBytes = Helpers::ReadFileBytes(rootPath / testImagePath);
		const std::vector<std::byte> testImage2Bytes = Helpers::ReadFileBytes(rootPath / testImage2Path);

		const Cocoa::Assets::Image& result1 = sut.LoadImage(testImagePath, testImageBytes);
		const Cocoa::Assets::Image& result2 = sut.LoadImage(testImage2Path, testImage2Bytes);

		EXPECT_NE(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadShader_ShouldReturnShaderSource_WhenProvidingPaths)
	{
		Cocoa::Assets::AssetManager sut;
		const std::string shaderId = "test-id";
		const std::string vertexPath = "Texts/sample.txt";
		const std::string fragmentPath = "Texts/sample2.txt";
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::vector<std::byte> vertexBytes = Helpers::ReadFileBytes(rootPath / vertexPath);
		const std::vector<std::byte> fragmentBytes = Helpers::ReadFileBytes(rootPath / fragmentPath);

		const Cocoa::Assets::ShaderSource& result = sut.LoadShader(shaderId, vertexBytes, fragmentBytes);

		EXPECT_NE(&result, nullptr);
	}

	TEST(AssetManagerTests, LoadShader_ShouldReturnSameShaderSource_WhenProvidingSameShaderId)
	{
		Cocoa::Assets::AssetManager sut;
		const std::string shaderId = "test-id";
		const std::string vertexPath = "Texts/sample.txt";
		const std::string fragmentPath = "Texts/sample2.txt";
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::vector<std::byte> vertexBytes = Helpers::ReadFileBytes(rootPath / vertexPath);
		const std::vector<std::byte> fragmentBytes = Helpers::ReadFileBytes(rootPath / fragmentPath);

		const Cocoa::Assets::ShaderSource& result1 = sut.LoadShader(shaderId, vertexBytes, fragmentBytes);
		const Cocoa::Assets::ShaderSource& result2 = sut.LoadShader(shaderId, vertexBytes, fragmentBytes);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(AssetManagerTests, LoadShader_ShouldReturnDifferentShaderSource_WhenProvidingDifferentShaderId)
	{
		Cocoa::Assets::AssetManager sut;
		const std::string vertexPath = "Texts/sample.txt";
		const std::string fragmentPath = "Texts/sample2.txt";
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::vector<std::byte> vertexBytes = Helpers::ReadFileBytes(rootPath / vertexPath);
		const std::vector<std::byte> fragmentBytes = Helpers::ReadFileBytes(rootPath / fragmentPath);

		const Cocoa::Assets::ShaderSource& result1 = sut.LoadShader("test-id", vertexBytes, fragmentBytes);
		const Cocoa::Assets::ShaderSource& result2 = sut.LoadShader("some-id", vertexBytes, fragmentBytes);

		EXPECT_NE(&result1, &result2);
	}
}