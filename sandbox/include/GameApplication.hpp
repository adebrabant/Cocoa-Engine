#pragma once

#include "core/Application.hpp"

namespace sandbox
{
	class GameApplication : public cocoa::core::Application
	{
	public:
		GameApplication();

	protected:
		void configureScenes(cocoa::scenes::SceneManager& sceneManager) override;
	};
}
