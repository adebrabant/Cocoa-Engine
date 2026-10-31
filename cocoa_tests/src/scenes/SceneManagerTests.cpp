#include "graphics/Viewport.hpp"
#include "stubs/graphics/StubGraphicsDevice.hpp"
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

namespace cocoa_tests::scenes
{
	struct TestScene : public cocoa::scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;

		void load(cocoa::assets::ResourceLoader& loader) override { loaded = true; }
		void unload(cocoa::assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct AnotherTestScene : public cocoa::scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;

		void load(cocoa::assets::ResourceLoader& loader) override { loaded = true; }
		void unload(cocoa::assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct CountingScene : public cocoa::scenes::Scene
	{
		int loadCount = 0;
		int unloadCount = 0;

		void load(cocoa::assets::ResourceLoader& loader) override { ++loadCount; }
		void unload(cocoa::assets::ResourceLoader& loader) override { ++unloadCount; }
	};

	struct ResourceLoaderTestContext
	{
		std::filesystem::path metadataPath = "test_data/metadata";
		std::filesystem::path ResourcePath = "test_data/Resources";

		cocoa::assets::JsonAssetDatabase JsonDatabase{ metadataPath };
		cocoa::assets::FilesystemAssetSource AssetSource{ ResourcePath };
		cocoa::assets::AssetManager AssetManager;

		stubs::StubGraphicsDevice GraphicsDevice;
		cocoa::graphics::TextureManager TextureManager{ GraphicsDevice };
		cocoa::graphics::ShaderManager ShaderManager{ GraphicsDevice };
		cocoa::graphics::MaterialManager MaterialManager;
		cocoa::graphics::SpriteManager SpriteManager;

		cocoa::assets::ResourceLoader ResourceLoader{
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
		cocoa::scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.setScene<TestScene>();
		auto testScene = manager.getScene<TestScene>();

		ASSERT_NE(testScene, nullptr);
		EXPECT_TRUE(testScene->loaded);
		EXPECT_FALSE(testScene->unloaded);
	}

	TEST(SceneManagerTests, SetScene_ShouldUnloadPreviousScene_WhenNewSceneIsAdded)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.setScene<TestScene>();
		manager.setScene<AnotherTestScene>();
		auto firstScene = manager.getScene<TestScene>();
		auto secondScene = manager.getScene<AnotherTestScene>();

		ASSERT_NE(firstScene, nullptr);
		ASSERT_NE(secondScene, nullptr);
		EXPECT_TRUE(firstScene->unloaded);
		EXPECT_TRUE(secondScene->loaded);
	}

	TEST(SceneManagerTests, AddScene_ShouldCreateNewScene)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.addScene<TestScene>();
		const auto scene = manager.getScene<TestScene>();

		ASSERT_NE(scene, nullptr);
	}

	TEST(SceneManagerTests, SetScene_ShouldNotCallUnload_WhenCurrentSceneEqualNewScene)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.setScene<TestScene>();
		const auto currentScene = dynamic_cast<TestScene*>(manager.getCurrentScene());
		manager.setScene<TestScene>();

		ASSERT_NE(currentScene, nullptr);
		EXPECT_FALSE(currentScene->unloaded);
	}

	TEST(SceneManagerTests, AddScene_ShouldNotCreateNewScene_WhenSceneExists)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.addScene<TestScene>();
		manager.setScene<TestScene>();
		auto secondScene = manager.getScene<TestScene>();
		manager.addScene<TestScene>();

		ASSERT_NE(secondScene, nullptr);
	}

	TEST(SceneManagerTests, GetScene_ShouldReturnNullptrIfSceneNotAdded)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::scenes::SceneManager manager(loaderContext.ResourceLoader);

		auto scene = manager.getScene<TestScene>();

		EXPECT_EQ(scene, nullptr);
	}

	TEST(SceneManagerTests, GetCurrentScene_ShouldReturnActiveScene)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.setScene<TestScene>();
		auto current = manager.getCurrentScene();

		ASSERT_NE(current, nullptr);
		EXPECT_NE(dynamic_cast<TestScene*>(current), nullptr);
	}

	TEST(SceneManagerTests, Unload_ShouldBeCalledExactlyOnce_WhenSceneReplaced)
	{
		ResourceLoaderTestContext loaderContext;
		cocoa::scenes::SceneManager manager(loaderContext.ResourceLoader);

		manager.setScene<CountingScene>();
		manager.setScene<AnotherTestScene>();

		auto scene = manager.getScene<CountingScene>();

		ASSERT_NE(scene, nullptr);
		EXPECT_EQ(scene->loadCount, 1);
		EXPECT_EQ(scene->unloadCount, 1);
	}
}
