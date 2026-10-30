#include "graphics/Viewport.hpp"
#include "stubs/Graphics/StubGraphicsDevice.hpp"
#include <assets/AssetManager.hpp>
#include <assets/FilesystemAssetSource.hpp>
#include <assets/JsonAssetDatabase.hpp>
#include <assets/ResourceLoader.hpp>
#include <graphics/MaterialManager.hpp>
#include <graphics/ShaderManager.hpp>
#include <graphics/SpriteManager.hpp>
#include <graphics/TextureManager.hpp>
#include <scenes/Scene.hpp>
#include <scenes/SceneManager.hpp>

#include <gtest/gtest.h>

namespace CocoaTests::Scenes
{
	struct TestScene : public cocoa::Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;

		void Load(cocoa::Assets::ResourceLoader& loader) override { loaded = true; }
		void Unload(cocoa::Assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct AnotherTestScene : public cocoa::Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;

		void Load(cocoa::Assets::ResourceLoader& loader) override { loaded = true; }
		void Unload(cocoa::Assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct CountingScene : public cocoa::Scenes::Scene
	{
		int loadCount = 0;
		int unloadCount = 0;

		void Load(cocoa::Assets::ResourceLoader& loader) override { ++loadCount; }
		void Unload(cocoa::Assets::ResourceLoader& loader) override { ++unloadCount; }
	};

	struct ResourceLoaderTestContext
	{
		std::filesystem::path MetadataPath = "TestData/Metadata";
		std::filesystem::path ResourcePath = "TestData/Resources";

		cocoa::Assets::JsonAssetDatabase JsonDatabase{ MetadataPath };
		cocoa::Assets::FilesystemAssetSource AssetSource{ ResourcePath };
		cocoa::Assets::AssetManager AssetManager;

		Stubs::StubGraphicsDevice GraphicsDevice;
		cocoa::Graphics::TextureManager TextureManager{ GraphicsDevice };
		cocoa::Graphics::ShaderManager ShaderManager{ GraphicsDevice };
		cocoa::Graphics::MaterialManager MaterialManager;
		cocoa::Graphics::SpriteManager SpriteManager;

		cocoa::Assets::ResourceLoader ResourceLoader{
			JsonDatabase,
			AssetSource,
			AssetManager,
			TextureManager,
			ShaderManager,
			MaterialManager,
			SpriteManager
		};
	};

	TEST(SceneManagerTests, SetScene_ShouldLoadNewScene_WhenNewSceneIsAdded)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.SetScene<TestScene>();
		auto testScene = manager.GetScene<TestScene>();

		ASSERT_NE(testScene, nullptr);
		EXPECT_TRUE(testScene->loaded);
		EXPECT_FALSE(testScene->unloaded);
	}

	TEST(SceneManagerTests, SetScene_ShouldUnloadPreviousScene_WhenNewSceneIsAdded)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader);

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
		cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.AddScene<TestScene>();
		const auto scene = manager.GetScene<TestScene>();

		ASSERT_NE(scene, nullptr);
	}

	TEST(SceneManagerTests, SetScene_ShouldNotCallUnload_WhenCurrentSceneEqualNewScene)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.SetScene<TestScene>();
		const auto currentScene = dynamic_cast<TestScene*>(manager.GetCurrentScene());
		manager.SetScene<TestScene>();

		ASSERT_NE(currentScene, nullptr);
		EXPECT_FALSE(currentScene->unloaded);
	}

	TEST(SceneManagerTests, AddScene_ShouldNotCreateNewScene_WhenSceneExists)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.AddScene<TestScene>();
		manager.SetScene<TestScene>();
		auto secondScene = manager.GetScene<TestScene>();
		manager.AddScene<TestScene>();

		ASSERT_NE(secondScene, nullptr);
	}

	TEST(SceneManagerTests, GetScene_ShouldReturnNullptrIfSceneNotAdded)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader);

		auto scene = manager.GetScene<TestScene>();

		EXPECT_EQ(scene, nullptr);
	}

	TEST(SceneManagerTests, GetCurrentScene_ShouldReturnActiveScene)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.SetScene<TestScene>();
		auto current = manager.GetCurrentScene();

		ASSERT_NE(current, nullptr);
		EXPECT_NE(dynamic_cast<TestScene*>(current), nullptr);
	}

	TEST(SceneManagerTests, Unload_ShouldBeCalledExactlyOnce_WhenSceneReplaced)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.SetScene<CountingScene>();
		manager.SetScene<AnotherTestScene>();

		auto scene = manager.GetScene<CountingScene>();

		ASSERT_NE(scene, nullptr);
		EXPECT_EQ(scene->loadCount, 1);
		EXPECT_EQ(scene->unloadCount, 1);
	}
}