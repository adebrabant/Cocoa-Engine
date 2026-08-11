#pragma once

#include "Chronos/FrameClock.hpp"
#include "Assets/AssetPathProvider.hpp"
#include "Platforms/WindowProperties.hpp"

#include <string>
#include <memory>

namespace Cocoa::Scenes
{
	class SceneManager;
}

namespace Cocoa::Core
{
	class Application
	{
	public:
		Application(uint32_t windowWidth, uint32_t windowHeight, const std::string& title);
		virtual ~Application() = default;
		void Run();

	protected:
		// ToDo: Need to come back to this
		virtual void ConfigureScenes(Scenes::SceneManager& sceneManager);

	private:
		Assets::AssetPathProvider m_assetPathProvider;
		Chronos::FrameClock m_frameClock;
		Platforms::WindowProperties m_windowProps;
	};
}