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
#include "Graphics/Viewport.hpp"

#include <gtest/gtest.h>

namespace Cocoa::Scenes::Tests
{
	struct TestScene : public Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;

		TestScene(const Graphics::Viewport& viewport)
			: Scene(viewport)
		{
		}

		void Load(Assets::ResourceLoader& loader) override { loaded = true; }
		void Unload(Assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct AnotherTestScene : public Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;

		AnotherTestScene(const Graphics::Viewport& viewport)
			: Scene(viewport)
		{
		}

		void Load(Assets::ResourceLoader& loader) override { loaded = true; }
		void Unload(Assets::ResourceLoader& loader) override { unloaded = true; }
	};

	struct CountingScene : public Scenes::Scene
	{
		int loadCount = 0;
		int unloadCount = 0;

		CountingScene(const Graphics::Viewport& viewport)
			: Scene(viewport)
		{
		}

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
		const Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.SetScene<TestScene>();
		auto testScene = manager.GetScene<TestScene>();

		ASSERT_NE(testScene, nullptr);
		EXPECT_TRUE(testScene->loaded);
		EXPECT_FALSE(testScene->unloaded);
	}

	TEST(SceneManagerTests, SetScene_ShouldUnloadPreviousScene_WhenNewSceneIsAdded)
	{
		const Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

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
		const Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.AddScene<TestScene>();
		const auto scene = manager.GetScene<TestScene>();

		ASSERT_NE(scene, nullptr);
	}

	TEST(SceneManagerTests, SetScene_ShouldNotCallUnload_WhenCurrentSceneEqualNewScene)
	{
		const Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.SetScene<TestScene>();
		const auto currentScene = dynamic_cast<TestScene*>(manager.GetCurrentScene());
		manager.SetScene<TestScene>();

		ASSERT_NE(currentScene, nullptr);
		EXPECT_FALSE(currentScene->unloaded);
	}

	TEST(SceneManagerTests, AddScene_ShouldNotCreateNewScene_WhenSceneExists)
	{
		const Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.AddScene<TestScene>();
		manager.SetScene<TestScene>();
		auto secondScene = manager.GetScene<TestScene>();
		manager.AddScene<TestScene>();

		ASSERT_NE(secondScene, nullptr);
	}

	TEST(SceneManagerTests, GetScene_ShouldReturnNullptrIfSceneNotAdded)
	{
		const Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		auto scene = manager.GetScene<TestScene>();

		EXPECT_EQ(scene, nullptr);
	}

	TEST(SceneManagerTests, GetCurrentScene_ShouldReturnActiveScene)
	{
		const Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.SetScene<TestScene>();
		auto current = manager.GetCurrentScene();

		ASSERT_NE(current, nullptr);
		EXPECT_NE(dynamic_cast<TestScene*>(current), nullptr);
	}

	TEST(SceneManagerTests, Unload_ShouldBeCalledExactlyOnce_WhenSceneReplaced)
	{
		const Graphics::Viewport viewport(0, 0, 800, 600);
		ResourceLoaderTestContext loaderContext;
		Scenes::SceneManager manager(loaderContext.ResourceLoader, viewport);

		manager.SetScene<CountingScene>();
		manager.SetScene<AnotherTestScene>();

		auto scene = manager.GetScene<CountingScene>();

		ASSERT_NE(scene, nullptr);
		EXPECT_EQ(scene->loadCount, 1);
		EXPECT_EQ(scene->unloadCount, 1);
	}
}