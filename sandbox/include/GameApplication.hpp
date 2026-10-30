#pragma once

#include "core/Application.hpp"

namespace Sandbox
{
	class GameApplication : public cocoa::Core::Application
	{
	public:
		GameApplication();

	protected:
		void ConfigureScenes(cocoa::Scenes::SceneManager& sceneManager) override;
	};
}