#include <Assets/FilesystemAssetSource.hpp>

#include <gtest/gtest.h>
#include <stdexcept>
#include <filesystem>

namespace Cocoa::Assets::Tests
{
	TEST(FilesystemAssetSourceTests, ReadBytes_ShouldReturnFileBytes_WhenRelativeFileExists)
	{
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::filesystem::path relativePath = "Images/test.png";
		const auto expectedSize = std::filesystem::file_size(rootPath / relativePath);
		const Assets::FilesystemAssetSource sut(rootPath);

		auto results = sut.ReadBytes(relativePath);

		EXPECT_EQ(results.size(), expectedSize);
	}

	TEST(FilesystemAssetSourceTests, ReadBytes_ShouldReturnFileBytes_WhenAbsoluteFilePathExisits)
	{
		const std::filesystem::path rootPath = std::filesystem::current_path() / "TestData" / "Resources";
		const std::filesystem::path relativePath = "Images/test.png";
		const auto expectedSize = std::filesystem::file_size(rootPath / relativePath);
		const Assets::FilesystemAssetSource sut(rootPath);

		auto results = sut.ReadBytes(relativePath);

		EXPECT_EQ(results.size(), expectedSize);
	}

	TEST(FilesystemAssetSourceTests, ReadBytes_ShouldThrowError_WhenFileDoesNotExist)
	{
		const std::filesystem::path rootPath = "TestData/Resources";
		const Assets::FilesystemAssetSource sut(rootPath);

		EXPECT_THROW(
			{
				sut.ReadBytes("badValue");
			},
			std::runtime_error
		);
	}

	TEST(FilesystemAssetSourceTests, Exists_ShouldReturnTrue_WhenFileExists)
	{
		const std::filesystem::path rootPath = "TestData/Resources";
		const std::filesystem::path relativePath = "Images/test.png";
		const Assets::FilesystemAssetSource sut(rootPath);

		auto result = sut.Exists(relativePath);

		EXPECT_TRUE(result);
	}

	TEST(FilesystemAssetSourceTests, Exists_ShouldReturnFalse_WhenFileDoesNotExist)
	{
		const std::filesystem::path rootPath = "TestData/Resources";
		const Assets::FilesystemAssetSource sut(rootPath);

		auto result = sut.Exists("badValue");

		EXPECT_FALSE(result);
	}
}