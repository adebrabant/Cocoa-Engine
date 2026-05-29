#include "Scenes/SceneManager.hpp"
#include <gtest/gtest.h>
#include <Scenes/Scene.hpp>

namespace Cocoa::Tests
{
	struct TestScene : public Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;
		void Load() override { loaded = true; }
		void Unload() override { unloaded = true; }
	};

	struct AnotherTestScene : public Scenes::Scene
	{
		bool loaded = false;
		bool unloaded = false;
		void Load() override { loaded = true; }
		void Unload() override { unloaded = true; }
	};

	struct CountingScene : public Scenes::Scene
	{
		int loadCount = 0;
		int unloadCount = 0;
		void Load() override { ++loadCount; }
		void Unload() override { ++unloadCount; }
	};

	TEST(SceneManagerTests, SetScene_ShouldLoadNewScene_WhenNewSceneIsAdded)
	{
		Scenes::SceneManager manager;

		manager.SetScene<TestScene>();
		auto testScene = manager.GetScene<TestScene>();

		ASSERT_NE(testScene, nullptr);
		EXPECT_TRUE(testScene->loaded);
		EXPECT_FALSE(testScene->unloaded);
	}

	TEST(SceneManagerTests, SetScene_ShouldUnloadPreviousScene_WhenNewSceneIsAdded)
	{
		Scenes::SceneManager manager;

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
		Scenes::SceneManager manager;

		manager.AddScene<TestScene>();
		auto scene = manager.GetScene<TestScene>();

		ASSERT_NE(scene, nullptr);
	}

	TEST(SceneManagerTests, SetScene_ShouldNotCallUnload_WhenCurrentSceneEqualNewScene)
	{
		Scenes::SceneManager manager;

		manager.SetScene<TestScene>();
		auto currentScene = dynamic_cast<TestScene*>(manager.GetCurrentScene());
		manager.SetScene<TestScene>();

		ASSERT_NE(currentScene, nullptr);
		EXPECT_FALSE(currentScene->unloaded);
	}

	TEST(SceneManagerTests, AddScene_ShouldNotCreateNewScene_WhenSceneExists)
	{
		Scenes::SceneManager manager;

		manager.AddScene<TestScene>();
		manager.SetScene<TestScene>();
		auto secondScene = manager.GetScene<TestScene>();
		manager.AddScene<TestScene>();

		ASSERT_NE(secondScene, nullptr);
	}

	TEST(SceneManagerTests, GetScene_ShouldReturnNullptrIfSceneNotAdded)
	{
		Scenes::SceneManager manager;

		auto scene = manager.GetScene<TestScene>();

		EXPECT_EQ(scene, nullptr);
	}

	TEST(SceneManagerTests, GetCurrentScene_ShouldReturnActiveScene)
	{
		Scenes::SceneManager manager;

		manager.SetScene<TestScene>();
		auto current = manager.GetCurrentScene();

		ASSERT_NE(current, nullptr);
		EXPECT_NE(dynamic_cast<TestScene*>(current), nullptr);
	}

	TEST(SceneManagerTests, Unload_ShouldBeCalledExactlyOnce_WhenSceneReplaced)
	{
		Scenes::SceneManager manager;

		manager.SetScene<CountingScene>();
		manager.SetScene<AnotherTestScene>();

		auto scene = manager.GetScene<CountingScene>();

		ASSERT_NE(scene, nullptr);
		EXPECT_EQ(scene->loadCount, 1);
		EXPECT_EQ(scene->unloadCount, 1);
	}
}