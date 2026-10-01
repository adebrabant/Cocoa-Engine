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

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenSpritesJsonDoesNotExist)
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
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.GetTextureInfo("dummy_idle1");

		EXPECT_EQ("dummy_idle1", result.Id);
		EXPECT_EQ("Textures/dummy-idle1.png", result.Path);
		EXPECT_EQ("RGBA8", result.Format);
		EXPECT_EQ("Linear", result.MinFilter);
		EXPECT_EQ("Linear", result.MagFilter);
		EXPECT_EQ("ClampToEdge", result.WrapS);
		EXPECT_EQ("ClampToEdge", result.WrapT);
		EXPECT_FALSE(result.GenerateMipmaps);
	}

	TEST(JsonAssetDatabaseTests, GetTextureInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			auto record = sut.GetTextureInfo("missing_texture"),
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, GetShaderInfo_ShouldReturnShaderRecord_WhenGivenValidId)
	{
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.GetShaderInfo("dummy_shader");

		EXPECT_EQ("Shaders/Sprite.vert", result.VertexPath);
		EXPECT_EQ("Shaders/Sprite.frag", result.FragmentPath);
	}

	TEST(JsonAssetDatabaseTests, GetShaderInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			auto record = sut.GetShaderInfo("missing_shader"),
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, GetMaterialInfo_ShouldReturnMaterialRecord_WhenGivenValidId)
	{
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.GetMaterialInfo("dummy_material");

		EXPECT_EQ("dummy_shader", result.ShaderId);
		EXPECT_EQ("Opaque", result.BlendMode);
		EXPECT_EQ(1.0, result.Tint.R);
		EXPECT_EQ(1.0, result.Tint.G);
		EXPECT_EQ(1.0, result.Tint.B);
		EXPECT_EQ(1.0, result.Tint.A);
	}

	TEST(JsonAssetDatabaseTests, GetMaterialInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			auto record = sut.GetMaterialInfo("missing_material"),
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, GetSpriteInfo_ShouldReturnSpriteRecord_WhenGivenValidId)
	{
		const std::string name{"dummy_sprite"};
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.GetSpriteInfo(name);

		EXPECT_EQ(name, result.Id);
		EXPECT_EQ("dummy_idle1", result.TextureId);
		EXPECT_EQ(0.0, result.MinPixel.X);
		EXPECT_EQ(0.0, result.MinPixel.Y);
		EXPECT_EQ(320.0, result.MaxPixel.X);
		EXPECT_EQ(180.0, result.MaxPixel.Y);
	}

	TEST(JsonAssetDatabaseTests, GetSpriteInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		const auto sut = Assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			auto record = sut.GetSpriteInfo("missing_sprite"),
			std::runtime_error
		);
	}
}