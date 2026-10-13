#include <Scenes/SceneManager.hpp>
#include <Assets/ResourceLoader.hpp>
#include <Scenes/Scene.hpp>
#include <Assets/JsonAssetDatabase.hpp>
#include <Assets/FilesystemAssetSource.hpp>
#include <Assets/AssetManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/TextureManager.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/SpriteManager.hpp>
#include "Stubs/Graphics/StubGraphicsDevice.hpp"
#include "Graphics/Viewport.hpp"

#include <gtest/gtest.h>

namespace CocoaTests::Scenes
{
	struct TestScene : public Cocoa::Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;

		TestScene(const Cocoa::Graphics::Viewport& viewport)
			: Scene(viewport)
		{
		}

		void Load(Cocoa::Assets::ResourceLoader& loader) override { loaded = true; }
		void Unload(Cocoa::Assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct AnotherTestScene : public Cocoa::Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;

		AnotherTestScene(const Cocoa::Graphics::Viewport& viewport)
			: Scene(viewport)
		{
		}

		void Load(Cocoa::Assets::ResourceLoader& loader) override { loaded = true; }
		void Unload(Cocoa::Assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct CountingScene : public Cocoa::Scenes::Scene
	{
		int loadCount = 0;
		int unloadCount = 0;

		CountingScene(const Cocoa::Graphics::Viewport& viewport)
			: Scene(viewport)
		{
		}

		void Load(Cocoa::Assets::ResourceLoader& loader) override { ++loadCount; }
		void Unload(Cocoa::Assets::ResourceLoader& loader) override { ++unloadCount; }
	};

	struct ResourceLoaderTestContext
	{
		std::filesystem::path MetadataPath = "TestData/Metadata";
		std::filesystem::path ResourcePath = "TestData/Resources";

		Cocoa::Assets::JsonAssetDatabase JsonDatabase{ MetadataPath };
		Cocoa::Assets::FilesystemAssetSource AssetSource{ ResourcePath };
		Cocoa::Assets::AssetManager AssetManager;

		Stubs::StubGraphicsDevice GraphicsDevice;
		Cocoa::Graphics::TextureManager TextureManager{ GraphicsDevice };
		Cocoa::Graphics::ShaderManager ShaderManager{ GraphicsDevice };
		Cocoa::Graphics::MaterialManager MaterialManager;
		Cocoa::Graphics::SpriteManager SpriteManager;

		Cocoa::Assets::ResourceLoader ResourceLoader{
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
		const Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.SetScene<TestScene>();
		auto testScene = manager.GetScene<TestScene>();

		ASSERT_NE(testScene, nullptr);
		EXPECT_TRUE(testScene->loaded);
		EXPECT_FALSE(testScene->unloaded);
	}

	TEST(SceneManagerTests, SetScene_ShouldUnloadPreviousScene_WhenNewSceneIsAdded)
	{
		const Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

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
		const Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.AddScene<TestScene>();
		const auto scene = manager.GetScene<TestScene>();

		ASSERT_NE(scene, nullptr);
	}

	TEST(SceneManagerTests, SetScene_ShouldNotCallUnload_WhenCurrentSceneEqualNewScene)
	{
		const Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.SetScene<TestScene>();
		const auto currentScene = dynamic_cast<TestScene*>(manager.GetCurrentScene());
		manager.SetScene<TestScene>();

		ASSERT_NE(currentScene, nullptr);
		EXPECT_FALSE(currentScene->unloaded);
	}

	TEST(SceneManagerTests, AddScene_ShouldNotCreateNewScene_WhenSceneExists)
	{
		const Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.AddScene<TestScene>();
		manager.SetScene<TestScene>();
		auto secondScene = manager.GetScene<TestScene>();
		manager.AddScene<TestScene>();

		ASSERT_NE(secondScene, nullptr);
	}

	TEST(SceneManagerTests, GetScene_ShouldReturnNullptrIfSceneNotAdded)
	{
		const Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		auto scene = manager.GetScene<TestScene>();

		EXPECT_EQ(scene, nullptr);
	}

	TEST(SceneManagerTests, GetCurrentScene_ShouldReturnActiveScene)
	{
		const Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.SetScene<TestScene>();
		auto current = manager.GetCurrentScene();

		ASSERT_NE(current, nullptr);
		EXPECT_NE(dynamic_cast<TestScene*>(current), nullptr);
	}

	TEST(SceneManagerTests, Unload_ShouldBeCalledExactlyOnce_WhenSceneReplaced)
	{
		const Cocoa::Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Cocoa::Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.SetScene<CountingScene>();
		manager.SetScene<AnotherTestScene>();

		auto scene = manager.GetScene<CountingScene>();

		ASSERT_NE(scene, nullptr);
		EXPECT_EQ(scene->loadCount, 1);
		EXPECT_EQ(scene->unloadCount, 1);
	}
}