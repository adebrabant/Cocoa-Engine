#include "stubs/Graphics/StubGraphicsDevice.hpp"
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

namespace CocoaTests::Assets
{
	const std::filesystem::path testMetadataPath = "TestData/Metadata";
	const std::filesystem::path testResourcePath = "TestData/Resources";

	TEST(ResourceLoaderTests, LoadTexture_ShouldReturnTextureHandle_WhenProvidingAssetTextureId)
	{
		cocoa::Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		cocoa::Assets::FilesystemAssetSource assetSource(testResourcePath);
		cocoa::Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
		cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		cocoa::Graphics::MaterialManager materialManager;
		cocoa::Graphics::SpriteManager spriteManager;
		cocoa::Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		cocoa::Graphics::TextureHandle result = sut.LoadTexture("dummy_idle1");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadShader_ShouldReturnShaderHandle_WhenProvidingShaderId)
	{
		cocoa::Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		cocoa::Assets::FilesystemAssetSource assetSource(testResourcePath);
		cocoa::Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
		cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		cocoa::Graphics::MaterialManager materialManager;
		cocoa::Graphics::SpriteManager spriteManager;
		cocoa::Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		cocoa::Graphics::ShaderHandle result = sut.LoadShader("dummy_shader");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingMaterialId)
	{
		cocoa::Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		cocoa::Assets::FilesystemAssetSource assetSource(testResourcePath);
		cocoa::Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
		cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		cocoa::Graphics::MaterialManager materialManager;
		cocoa::Graphics::SpriteManager spriteManager;
		cocoa::Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		cocoa::Graphics::MaterialHandle result = sut.LoadMaterial("dummy_material");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadSprite_ShouldReturnSpriteHandle_WhenProvidingSpriteId)
	{
		cocoa::Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		cocoa::Assets::FilesystemAssetSource assetSource(testResourcePath);
		cocoa::Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
		cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		cocoa::Graphics::MaterialManager materialManager;
		cocoa::Graphics::SpriteManager spriteManager;
		cocoa::Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		const cocoa::Graphics::SpriteHandle result = sut.LoadSprite("dummy_sprite");

		EXPECT_EQ(result.Id, 1);
	}
}