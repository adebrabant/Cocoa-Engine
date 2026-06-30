#pragma once

#include "Core/Application.hpp"

namespace Sandbox
{
	class GameApplication : public Cocoa::Core::Application
	{
	public:
		GameApplication();

	protected:
		void ConfigureScenes(Cocoa::Scenes::SceneManager& sceneManager) override;
	};
}