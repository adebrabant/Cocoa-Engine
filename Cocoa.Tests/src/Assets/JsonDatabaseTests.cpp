#include <gtest/gtest.h>
#include <Assets/JsonAssetDatabase.hpp>
#include <Core/Color.hpp>

#include <string>
#include <stdexcept>
#include <filesystem>

namespace Cocoa::Tests
{
	const std::filesystem::path testMetadataPath = "TestData/Metadata";

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenTexturesJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "TestData/MissingTexturesJson";

		EXPECT_THROW(
			{
				Assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenShadersJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "TestData/MissingShadersJson";

		EXPECT_THROW(
			{
				Assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenMaterialsJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "TestData/MissingMaterialsJson";

		EXPECT_THROW(
			{
				Assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, GetTextureInfo_ShouldReturnTextureRecord_WhenGivenValidId)
	{
		auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.GetTextureInfo("dummy_idle1");

		EXPECT_EQ(result.Id, "dummy_idle1");
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

	TEST(JsonAssetDatabaseTests, GetShaderInfo_ShouldReturnShaderRecord_WhenGivenValidId)
	{
		auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.GetShaderInfo("dummy_shader");

		EXPECT_EQ(result.VertexPath, "Shaders/Dummy.vert");
		EXPECT_EQ(result.FragmentPath, "Shaders/Dummy.frag");
	}

	TEST(JsonAssetDatabaseTests, GetShaderInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			sut.GetShaderInfo("missing_shader"),
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, GetMaterialInfo_ShouldReturnMaterialRecord_WhenGivenValidId)
	{
		auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.GetMaterialInfo("dummy_material");

		EXPECT_EQ(result.ShaderId, "dummy_shader");
		EXPECT_EQ(result.TextureId, "dummy_texture");
		EXPECT_EQ(result.Tint.R, 1.0);
		EXPECT_EQ(result.Tint.G, 1.0);
		EXPECT_EQ(result.Tint.B, 1.0);
		EXPECT_EQ(result.Tint.A, 1.0);
	}

	TEST(JsonAssetDatabaseTests, GetMaterialInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			sut.GetMaterialInfo("missing_material"),
			std::runtime_error
		);
	}
}