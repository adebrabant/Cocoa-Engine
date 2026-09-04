#include <gtest/gtest.h>
#include <Assets/JsonAssetDatabase.hpp>
#include <Core/Color.hpp>

#include <string>
#include <stdexcept>
#include <filesystem>

namespace Cocoa::Assets::Tests
{
	const std::filesystem::path testMetadataPath = "TestData/Metadata";

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenTexturesJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "TestData/MissingTextures";

		EXPECT_THROW(
			{
				Assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenShadersJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "TestData/MissingShaders";

		EXPECT_THROW(
			{
				Assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenMaterialsJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "TestData/MissingMaterials";

		EXPECT_THROW(
			{
				Assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenSprtiesJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "TestData/MissingSprites";

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

		EXPECT_EQ(result.VertexPath, "Shaders/Sprite.vert");
		EXPECT_EQ(result.FragmentPath, "Shaders/Sprite.frag");
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
		EXPECT_EQ(result.TextureId, "dummy_idle1");
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

	TEST(JsonAssetDatabaseTests, GetSpriteInfo_ShouldReturnSpriteRecord_WhenGivenValidId)
	{
		const std::string name{"dummy_sprite"};
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.GetSpriteInfo(name);

		EXPECT_EQ(result.Id, name);
		EXPECT_EQ(result.TextureId, "dummy_idle1");
		EXPECT_EQ(result.MinUV.X, 0.0);
		EXPECT_EQ(result.MinUV.Y, 0.0);
		EXPECT_EQ(result.MaxUV.X, 1.0);
		EXPECT_EQ(result.MaxUV.Y, 1.0);
	}

	TEST(JsonAssetDatabaseTests, GetSpriteInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			sut.GetSpriteInfo("missing_sprite"),
			std::runtime_error
		);
	}
}