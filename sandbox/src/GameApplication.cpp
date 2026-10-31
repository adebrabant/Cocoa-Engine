#include "GameApplication.hpp"
#include "scenes/TestScene.hpp"
#include <core/Application.hpp>
#include <scenes/SceneManager.hpp>

namespace sandbox
{
	GameApplication::GameApplication()
		: Application(1920, 1080, "Sandbox")
	{

	}

	void GameApplication::configureScenes(cocoa::scenes::SceneManager& sceneManager)
	{
		sceneManager.addScene<TestScene>();
		sceneManager.setScene<TestScene>();
	}
}
