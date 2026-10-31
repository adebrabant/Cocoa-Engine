#include <assets/FilesystemAssetSource.hpp>

#include <filesystem>
#include <gtest/gtest.h>
#include <stdexcept>

namespace cocoa_tests::assets
{
	TEST(FilesystemAssetSourceTests, ReadBytes_ShouldReturnFileBytes_WhenRelativeFileExists)
	{
		const std::filesystem::path rootPath = "test_data/resources";
		const std::filesystem::path relativePath = "images/test.png";
		const auto expectedSize = std::filesystem::file_size(rootPath / relativePath);
		const cocoa::assets::FilesystemAssetSource sut(rootPath);

		auto results = sut.readBytes(relativePath);

		EXPECT_EQ(results.size(), expectedSize);
	}

	TEST(FilesystemAssetSourceTests, ReadBytes_ShouldReturnFileBytes_WhenAbsoluteFilePathExisits)
	{
		const std::filesystem::path rootPath = std::filesystem::current_path() / "test_data" / "resources";
		const std::filesystem::path relativePath = "images/test.png";
		const auto expectedSize = std::filesystem::file_size(rootPath / relativePath);
		const cocoa::assets::FilesystemAssetSource sut(rootPath);

		auto results = sut.readBytes(relativePath);

		EXPECT_EQ(results.size(), expectedSize);
	}

	TEST(FilesystemAssetSourceTests, ReadBytes_ShouldThrowError_WhenFileDoesNotExist)
	{
		const std::filesystem::path rootPath = "test_data/resources";
		const cocoa::assets::FilesystemAssetSource sut(rootPath);

		EXPECT_THROW(
			{
				sut.readBytes("badValue");
			},
			std::runtime_error
		);
	}

	TEST(FilesystemAssetSourceTests, Exists_ShouldReturnTrue_WhenFileExists)
	{
		const std::filesystem::path rootPath = "test_data/resources";
		const std::filesystem::path relativePath = "images/test.png";
		const cocoa::assets::FilesystemAssetSource sut(rootPath);

		auto result = sut.exists(relativePath);

		EXPECT_TRUE(result);
	}

	TEST(FilesystemAssetSourceTests, Exists_ShouldReturnFalse_WhenFileDoesNotExist)
	{
		const std::filesystem::path rootPath = "test_data/resources";
		const cocoa::assets::FilesystemAssetSource sut(rootPath);

		auto result = sut.exists("badValue");

		EXPECT_FALSE(result);
	}
}
