#include <Scenes/SceneManager.hpp>
#include <Assets/ResourceLoader.hpp>
#include <Scenes/Scene.hpp>
#include <Assets/JsonAssetDatabase.hpp>
#include <Assets/FilesystemAssetSource.hpp>
#include <Assets/AssetManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/TextureManager.hpp>
#include <Graphics/MaterialManager.hpp>
#include "Stubs/Graphics/StubGraphicsDevice.hpp"

#include <gtest/gtest.h>

namespace Cocoa::Scenes::Tests
{
	struct TestScene : public Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;
		void Load(Assets::ResourceLoader& loader) override { loaded = true; }
		void Unload(Assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct AnotherTestScene : public Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;
		void Load(Assets::ResourceLoader& loader) override { loaded = true; }
		void Unload(Assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct CountingScene : public Scenes::Scene
	{
		int loadCount = 0;
		int unloadCount = 0;
		void Load(Assets::ResourceLoader& loader) override { ++loadCount; }
		void Unload(Assets::ResourceLoader& loader) override { ++unloadCount; }
	};

	struct ResourceLoaderTestContext
	{
		std::filesystem::path MetadataPath = "TestData/Metadata";
		std::filesystem::path ResourcePath = "TestData/Resources";

		Assets::JsonAssetDatabase JsonDatabase{ MetadataPath };
		Assets::FilesystemAssetSource AssetSource{ ResourcePath };
		Assets::AssetManager AssetManager;

		Stubs::StubGraphicsDevice GraphicsDevice;
		Graphics::TextureManager TextureManager{ GraphicsDevice };
		Graphics::ShaderManager ShaderManager{ GraphicsDevice };
		Graphics::MaterialManager MaterialManager;

		Assets::ResourceLoader ResourceLoader{
			JsonDatabase,
			AssetSource,
			AssetManager,
			TextureManager,
			ShaderManager,
			MaterialManager
		};
	};

	TEST(SceneManagerTests, SetScene_ShouldLoadNewScene_WhenNewSceneIsAdded)
	{
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.SetScene<TestScene>();
		auto testScene = manager.GetScene<TestScene>();

		ASSERT_NE(testScene, nullptr);
		EXPECT_TRUE(testScene->loaded);
		EXPECT_FALSE(testScene->unloaded);
	}

	TEST(SceneManagerTests, SetScene_ShouldUnloadPreviousScene_WhenNewSceneIsAdded)
	{
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.SetScene<TestScene>();
		manager.SetScene<AnotherTestScene>();
		auto firstScene = manager.GetScene<TestScene>();
		auto secondScene = manager.GetScene<AnotherTestScene>();

		ASSERT_NE(firstScene, nullptr);
		ASSERT_NE(secondScene, nullptr);
		EXPECT_TRUE(firstScene->unloaded);
		EXPECT_TRUE(secondScene->loaded);
	}

	TEST(SceneManagerTests, AddScene_ShouldCreateNewScene)
	{
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.AddScene<TestScene>();
		auto scene = manager.GetScene<TestScene>();

		ASSERT_NE(scene, nullptr);
	}

	TEST(SceneManagerTests, SetScene_ShouldNotCallUnload_WhenCurrentSceneEqualNewScene)
	{
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.SetScene<TestScene>();
		auto currentScene = dynamic_cast<TestScene*>(manager.GetCurrentScene());
		manager.SetScene<TestScene>();

		ASSERT_NE(currentScene, nullptr);
		EXPECT_FALSE(currentScene->unloaded);
	}

	TEST(SceneManagerTests, AddScene_ShouldNotCreateNewScene_WhenSceneExists)
	{
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.AddScene<TestScene>();
		manager.SetScene<TestScene>();
		auto secondScene = manager.GetScene<TestScene>();
		manager.AddScene<TestScene>();

		ASSERT_NE(secondScene, nullptr);
	}

	TEST(SceneManagerTests, GetScene_ShouldReturnNullptrIfSceneNotAdded)
	{
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader);

		auto scene = manager.GetScene<TestScene>();

		EXPECT_EQ(scene, nullptr);
	}

	TEST(SceneManagerTests, GetCurrentScene_ShouldReturnActiveScene)
	{
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.SetScene<TestScene>();
		auto current = manager.GetCurrentScene();

		ASSERT_NE(current, nullptr);
		EXPECT_NE(dynamic_cast<TestScene*>(current), nullptr);
	}

	TEST(SceneManagerTests, Unload_ShouldBeCalledExactlyOnce_WhenSceneReplaced)
	{
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.SetScene<CountingScene>();
		manager.SetScene<AnotherTestScene>();

		auto scene = manager.GetScene<CountingScene>();

		ASSERT_NE(scene, nullptr);
		EXPECT_EQ(scene->loadCount, 1);
		EXPECT_EQ(scene->unloadCount, 1);
	}
}