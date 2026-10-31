#include <assets/JsonAssetDatabase.hpp>
#include <core/Color.hpp>
#include <gtest/gtest.h>

#include <string>
#include <stdexcept>
#include <filesystem>

namespace cocoa_tests::assets
{
	const std::filesystem::path testMetadataPath = "test_data/metadata";

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenTexturesJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "test_data/missing_textures";

		EXPECT_THROW(
			{
				cocoa::assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenShadersJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "test_data/missing_shaders";

		EXPECT_THROW(
			{
				cocoa::assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenMaterialsJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "test_data/missing_materials";

		EXPECT_THROW(
			{
				cocoa::assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, Constructor_ShouldThrowError_WhenSpritesJsonDoesNotExist)
	{
		const std::filesystem::path metadataPath = "test_data/missing_sprites";

		EXPECT_THROW(
			{
				cocoa::assets::JsonAssetDatabase sut(metadataPath);
			},
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, GetTextureInfo_ShouldReturnTextureRecord_WhenGivenValidId)
	{
		const auto sut = cocoa::assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.getTextureInfo("dummy_idle1");

		EXPECT_EQ("dummy_idle1", result.id);
		EXPECT_EQ("textures/dummy-idle1.png", result.path);
		EXPECT_EQ("RGBA8", result.format);
		EXPECT_EQ("Linear", result.minFilter);
		EXPECT_EQ("Linear", result.magFilter);
		EXPECT_EQ("ClampToEdge", result.wrapS);
		EXPECT_EQ("ClampToEdge", result.wrapT);
		EXPECT_FALSE(result.generateMipmaps);
	}

	TEST(JsonAssetDatabaseTests, GetTextureInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		const auto sut = cocoa::assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			auto record = sut.getTextureInfo("missing_texture"),
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, GetShaderInfo_ShouldReturnShaderRecord_WhenGivenValidId)
	{
		const auto sut = cocoa::assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.getShaderInfo("dummy_shader");

		EXPECT_EQ("shaders/sprite.vert", result.vertexPath);
		EXPECT_EQ("shaders/sprite.frag", result.fragmentPath);
	}

	TEST(JsonAssetDatabaseTests, GetShaderInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		const auto sut = cocoa::assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			auto record = sut.getShaderInfo("missing_shader"),
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, GetMaterialInfo_ShouldReturnMaterialRecord_WhenGivenValidId)
	{
		const auto sut = cocoa::assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.getMaterialInfo("dummy_material");

		EXPECT_EQ("dummy_shader", result.shaderId);
		EXPECT_EQ("opaque", result.blendMode);
		EXPECT_EQ(1.0, result.tint.r);
		EXPECT_EQ(1.0, result.tint.g);
		EXPECT_EQ(1.0, result.tint.b);
		EXPECT_EQ(1.0, result.tint.a);
	}

	TEST(JsonAssetDatabaseTests, GetMaterialInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		const auto sut = cocoa::assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			auto record = sut.getMaterialInfo("missing_material"),
			std::runtime_error
		);
	}

	TEST(JsonAssetDatabaseTests, GetSpriteInfo_ShouldReturnSpriteRecord_WhenGivenValidId)
	{
		const std::string name{"dummy_sprite"};
		const auto sut = cocoa::assets::JsonAssetDatabase(testMetadataPath);

		const auto& result = sut.getSpriteInfo(name);

		EXPECT_EQ(name, result.id);
		EXPECT_EQ("dummy_idle1", result.textureId);
		EXPECT_EQ(0.0, result.minPixel.x);
		EXPECT_EQ(0.0, result.minPixel.y);
		EXPECT_EQ(320.0, result.maxPixel.x);
		EXPECT_EQ(180.0, result.maxPixel.y);
	}

	TEST(JsonAssetDatabaseTests, GetSpriteInfo_ShouldThrowError_WhenGivenInvalidId)
	{
		const auto sut = cocoa::assets::JsonAssetDatabase(testMetadataPath);

		EXPECT_THROW(
			auto record = sut.getSpriteInfo("missing_sprite"),
			std::runtime_error
		);
	}
}
