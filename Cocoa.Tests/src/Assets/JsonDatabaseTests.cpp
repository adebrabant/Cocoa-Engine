#include <gtest/gtest.h>
#include <Assets/JsonAssetDatabase.hpp>

#include <string>
#include <stdexcept>
#include <filesystem>

namespace Cocoa::Tests
{
	const std::filesystem::path testMetadataPath = "TestData/Metadata";

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenTexturesJsonDoesNotExist)
	{
		std::filesystem::path missingMetadataPath = "TestData/MissingMetadata";

		EXPECT_THROW(
			{
				Assets::JsonAssetDatabase sut(missingMetadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenTextureRecordIsMissingPath)
	{
		std::filesystem::path metadataPath = "TestData/InvalidMetadataMissingPath";

		EXPECT_THROW(
			{
				Assets::JsonAssetDatabase sut(metadataPath);
			},
			std::exception
		);
	}

	TEST(JsonAssetDatabaseTests, GetTextureInfo_ShouldReturnTextureRecord_WhenGivenValidId)
	{
		auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.GetTextureInfo("dummy-idle1");

		EXPECT_EQ(result.Id, "dummy-idle1");
		EXPECT_EQ(result.Path, "Textures/dummy-idle1.png");
		EXPECT_EQ(result.Format, "RGBA8");
		EXPECT_EQ(result.MinFilter, "Linear");
		EXPECT_EQ(result.MagFilter, "Linear");
		EXPECT_EQ(result.WrapS, "ClampToEdge");
		EXPECT_EQ(result.WrapT, "ClampToEdge");
		EXPECT_FALSE(result.GenerateMipmaps);
	}

	TEST(JsonAssetDatabaseTests, GetTextureInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			sut.GetTextureInfo("missing_texture"),
			std::runtime_error
		);
	}
}