#pragma once

#include "FrameClock.hpp"
#include "assets/AssetPathProvider.hpp"
#include "events/EventBus.hpp"
#include "platforms/WindowProperties.hpp"
#include "utilities/Memory.hpp"

#include <string>

namespace cocoa::Scenes
{
	class SceneManager;
}

namespace cocoa::Graphics
{
	class GraphicsDevice;
}

namespace cocoa::Core
{
	class Application
	{
	public:
		Application(uint32_t windowWidth, uint32_t windowHeight, const std::string& title);
		virtual ~Application();
		void Run();

	protected:
		// ToDo: Need to come back to this
		virtual void ConfigureScenes(Scenes::SceneManager& sceneManager);

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		Assets::AssetPathProvider m_assetPathProvider;
		Chronos::FrameClock m_frameClock;
		Platforms::WindowProperties m_windowProps;
		Events::EventBus m_eventBus;
		Unique<Graphics::GraphicsDevice> m_graphicsDevice;
		Events::EventBus::SubscriptionToken m_FramebufferResizeEventToken;
	};
}
