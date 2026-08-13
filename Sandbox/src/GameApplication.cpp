#include "GameApplication.hpp"
#include "Scenes/TestScene.hpp"
#include <Core/Application.hpp>
#include <Scenes/SceneManager.hpp>

namespace Sandbox
{
	GameApplication::GameApplication() 
		: Application(1920, 1080, "Sandbox")
	{

	}

	void GameApplication::ConfigureScenes(Cocoa::Scenes::SceneManager& sceneManager)
	{
		sceneManager.AddScene<TestScene>();
		sceneManager.SetScene<TestScene>();
	}
}