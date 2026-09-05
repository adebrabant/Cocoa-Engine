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

namespace Cocoa::Assets::Tests
{
	const std::filesystem::path testMetadataPath = "TestData/Metadata";
	const std::filesystem::path testResourcePath = "TestData/Resources";

	TEST(ResourceLoaderTests, LoadTexture_ShouldReturnTextureHandle_WhenProvidingAssetTextureId)
	{
		Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Assets::FilesystemAssetSource assetSource(testResourcePath);
		Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Graphics::TextureManager textureManager(stubGraphicsDevice);
		Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Graphics::MaterialManager materialManager;
		Graphics::SpriteManager spriteManager;
		Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		Graphics::TextureHandle result = sut.LoadTexture("dummy_idle1");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadShader_ShouldReturnShaderHandle_WhenProvidingShaderId)
	{
		Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Assets::FilesystemAssetSource assetSource(testResourcePath);
		Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Graphics::TextureManager textureManager(stubGraphicsDevice);
		Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Graphics::MaterialManager materialManager;
		Graphics::SpriteManager spriteManager;
		Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		Graphics::ShaderHandle result = sut.LoadShader("dummy_shader");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingMaterialId)
	{
		Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Assets::FilesystemAssetSource assetSource(testResourcePath);
		Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Graphics::TextureManager textureManager(stubGraphicsDevice);
		Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Graphics::MaterialManager materialManager;
		Graphics::SpriteManager spriteManager;
		Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		Graphics::MaterialHandle result = sut.LoadMaterial("dummy_material");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadSprite_ShouldReturnSpriteHandle_WhenProvidingSpriteId)
	{
		Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Assets::FilesystemAssetSource assetSource(testResourcePath);
		Assets::AssetManager assetManager;
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Graphics::TextureManager textureManager(stubGraphicsDevice);
		Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Graphics::MaterialManager materialManager;
		Graphics::SpriteManager spriteManager;
		Assets::ResourceLoader sut(
			jsonDatabase,
			assetSource,
			assetManager,
			textureManager,
			shaderManager,
			materialManager,
			spriteManager
		);

		const Graphics::SpriteHandle result = sut.LoadSprite("dummy_sprite");

		EXPECT_EQ(result.Id, 1);
	}
}