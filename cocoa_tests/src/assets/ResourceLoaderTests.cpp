#include "stubs/graphics/StubGraphicsDevice.hpp"
#include <assets/AssetManager.hpp>
#include <assets/FilesystemAssetSource.hpp>
#include <assets/JsonAssetDatabase.hpp>
#include <assets/ResourceLoader.hpp>
#include <graphics/GraphicsHandles.hpp>
#include <graphics/MaterialManager.hpp>
#include <graphics/ShaderManager.hpp>
#include <graphics/SpriteManager.hpp>
#include <graphics/TextureManager.hpp>

#include <gtest/gtest.h>
#include <string>
#include <filesystem>

namespace cocoa_tests::assets
{
	const std::filesystem::path testMetadataPath = "test_data/metadata";
	const std::filesystem::path testResourcePath = "test_data/resources";

	TEST(ResourceLoaderTests, LoadTexture_ShouldReturnTextureHandle_WhenProvidingAssetTextureId)
	{
		cocoa::assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		cocoa::assets::FilesystemAssetSource assetSource(testResourcePath);
		cocoa::assets::AssetManager assetManager;
		stubs::StubGraphicsDevice stubGraphicsDevice;
		cocoa::graphics::TextureManager textureManager(stubGraphicsDevice);
		cocoa::graphics::ShaderManager shaderManager(stubGraphicsDevice);
		cocoa::graphics::MaterialManager materialManager;
		cocoa::graphics::SpriteManager spriteManager;
		cocoa::assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		cocoa::graphics::TextureHandle result = sut.loadTexture("dummy_idle1");

		EXPECT_EQ(result.id, 1);
	}

	TEST(ResourceLoaderTests, LoadShader_ShouldReturnShaderHandle_WhenProvidingShaderId)
	{
		cocoa::assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		cocoa::assets::FilesystemAssetSource assetSource(testResourcePath);
		cocoa::assets::AssetManager assetManager;
		stubs::StubGraphicsDevice stubGraphicsDevice;
		cocoa::graphics::TextureManager textureManager(stubGraphicsDevice);
		cocoa::graphics::ShaderManager shaderManager(stubGraphicsDevice);
		cocoa::graphics::MaterialManager materialManager;
		cocoa::graphics::SpriteManager spriteManager;
		cocoa::assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		cocoa::graphics::ShaderHandle result = sut.loadShader("dummy_shader");

		EXPECT_EQ(result.id, 1);
	}

	TEST(ResourceLoaderTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingMaterialId)
	{
		cocoa::assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		cocoa::assets::FilesystemAssetSource assetSource(testResourcePath);
		cocoa::assets::AssetManager assetManager;
		stubs::StubGraphicsDevice stubGraphicsDevice;
		cocoa::graphics::TextureManager textureManager(stubGraphicsDevice);
		cocoa::graphics::ShaderManager shaderManager(stubGraphicsDevice);
		cocoa::graphics::MaterialManager materialManager;
		cocoa::graphics::SpriteManager spriteManager;
		cocoa::assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		cocoa::graphics::MaterialHandle result = sut.loadMaterial("dummy_material");

		EXPECT_EQ(result.id, 1);
	}

	TEST(ResourceLoaderTests, LoadSprite_ShouldReturnSpriteHandle_WhenProvidingSpriteId)
	{
		cocoa::assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		cocoa::assets::FilesystemAssetSource assetSource(testResourcePath);
		cocoa::assets::AssetManager assetManager;
		stubs::StubGraphicsDevice stubGraphicsDevice;
		cocoa::graphics::TextureManager textureManager(stubGraphicsDevice);
		cocoa::graphics::ShaderManager shaderManager(stubGraphicsDevice);
		cocoa::graphics::MaterialManager materialManager;
		cocoa::graphics::SpriteManager spriteManager;
		cocoa::assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		const cocoa::graphics::SpriteHandle result = sut.loadSprite("dummy_sprite");

		EXPECT_EQ(result.id, 1);
	}
}
