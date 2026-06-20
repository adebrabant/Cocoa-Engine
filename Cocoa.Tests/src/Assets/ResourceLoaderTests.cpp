#include <Assets/ResourceLoader.hpp>
#include <Assets/JsonAssetDatabase.hpp>
#include <Assets/AssetManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/TextureManager.hpp>
#include <Graphics/MaterialManager.hpp>
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
		Assets::AssetManager assetManager(testResourcePath);
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Graphics::TextureManager textureManager(stubGraphicsDevice);
		Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Graphics::MaterialManager materialManager;
		Assets::ResourceLoader sut(
			jsonDatabase,
			assetManager,
			textureManager,
			shaderManager,
			materialManager
		);

		Graphics::TextureHandle result = sut.LoadTexture("dummy_idle1");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadShader_ShouldReturnShaderHandle_WhenProvidingShaderId)
	{
		Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Assets::AssetManager assetManager(testResourcePath);
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Graphics::TextureManager textureManager(stubGraphicsDevice);
		Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Graphics::MaterialManager materialManager;
		Assets::ResourceLoader sut(
			jsonDatabase,
			assetManager,
			textureManager,
			shaderManager,
			materialManager
		);

		Graphics::ShaderHandle result = sut.LoadShader("dummy_shader");

		EXPECT_EQ(result.Id, 1);
	}

	TEST(ResourceLoaderTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingMaterialId)
	{
		Assets::JsonAssetDatabase jsonDatabase(testMetadataPath);
		Assets::AssetManager assetManager(testResourcePath);
		Stubs::StubGraphicsDevice stubGraphicsDevice;
		Graphics::TextureManager textureManager(stubGraphicsDevice);
		Graphics::ShaderManager shaderManager(stubGraphicsDevice);
		Graphics::MaterialManager materialManager;
		Assets::ResourceLoader sut(
			jsonDatabase,
			assetManager,
			textureManager,
			shaderManager,
			materialManager
		);

		Graphics::MaterialHandle result = sut.LoadMaterial("dummy_material");

		EXPECT_EQ(result.Id, 1);
	}
}