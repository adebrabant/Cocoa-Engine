#include <Assets/ResourceLoader.hpp>
#include <Assets/JsonAssetDatabase.hpp>
#include <Assets/FilesystemAssetSource.hpp>
#include <Assets/AssetManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/TextureManager.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/SpriteManager.hpp>
#include <Graphics/GraphicsHandles.hpp>
#include "Stubs/Graphics/StubGraphicsDevice.hpp"

#include <gtest/gtest.h>
#include <string>
#include <filesystem>

namespace CocoaTests::Assets
{
	const std::filesystem::path testMetadataPath = "TestData/Metadata";
	const std::filesystem::path testResourcePath = "TestData/Resources";

	TEST(ResourceLoaderTests, LoadTexture_ShouldReturnTextureHandle_WhenProvidingAssetTextureId)
	{
		Cocoa::Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Cocoa::Assets::FilesystemAssetSource assetSource(testResourcePath);
		Cocoa::Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
		Cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Cocoa::Graphics::MaterialManager materialManager;
		Cocoa::Graphics::SpriteManager spriteManager;
		Cocoa::Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		Cocoa::Graphics::TextureHandle result = sut.LoadTexture("dummy_idle1");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadShader_ShouldReturnShaderHandle_WhenProvidingShaderId)
	{
		Cocoa::Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Cocoa::Assets::FilesystemAssetSource assetSource(testResourcePath);
		Cocoa::Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
		Cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Cocoa::Graphics::MaterialManager materialManager;
		Cocoa::Graphics::SpriteManager spriteManager;
		Cocoa::Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		Cocoa::Graphics::ShaderHandle result = sut.LoadShader("dummy_shader");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingMaterialId)
	{
		Cocoa::Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Cocoa::Assets::FilesystemAssetSource assetSource(testResourcePath);
		Cocoa::Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
		Cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Cocoa::Graphics::MaterialManager materialManager;
		Cocoa::Graphics::SpriteManager spriteManager;
		Cocoa::Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		Cocoa::Graphics::MaterialHandle result = sut.LoadMaterial("dummy_material");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadSprite_ShouldReturnSpriteHandle_WhenProvidingSpriteId)
	{
		Cocoa::Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Cocoa::Assets::FilesystemAssetSource assetSource(testResourcePath);
		Cocoa::Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
		Cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Cocoa::Graphics::MaterialManager materialManager;
		Cocoa::Graphics::SpriteManager spriteManager;
		Cocoa::Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		const Cocoa::Graphics::SpriteHandle result = sut.LoadSprite("dummy_sprite");

		EXPECT_EQ(result.Id, 1);
	}
}