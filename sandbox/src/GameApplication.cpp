#include "GameApplication.hpp"
#include "../../cocoa/include/scenes/TestScene.hpp"
#include <core/Application.hpp>
#include <scenes/SceneManager.hpp>

namespace Sandbox
{
	GameApplication::GameApplication() 
		: Application(1920, 1080, "Sandbox")
	{

	}

	void GameApplication::ConfigureScenes(cocoa::Scenes::SceneManager& sceneManager)
	{
		sceneManager.AddScene<TestScene>();
		sceneManager.SetScene<TestScene>();
	}
}