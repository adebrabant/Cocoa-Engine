#pragma once

#include "FrameClock.hpp"
#include "assets/AssetPathProvider.hpp"
#include "events/EventBus.hpp"
#include "platforms/WindowProperties.hpp"
#include "utilities/Memory.hpp"

#include <string>

namespace cocoa::scenes
{
	class SceneManager;
}

namespace cocoa::graphics
{
	class GraphicsDevice;
}

namespace cocoa::core
{
	class Application
	{
	public:
		Application(uint32_t windowWidth, uint32_t windowHeight, const std::string& title);
		virtual ~Application();
		void Run();

	protected:
		// ToDo: Need to come back to this
		virtual void configureScenes(scenes::SceneManager& sceneManager);

	private:
		void registerEventHandlers();
		void unregisterEventHandlers();

	private:
		assets::AssetPathProvider m_assetPathProvider;
		FrameClock m_frameClock;
		platforms::WindowProperties m_windowProps;
		events::EventBus m_eventBus;
		Unique<graphics::GraphicsDevice> m_graphicsDevice;
		events::EventBus::SubscriptionToken m_FramebufferResizeEventToken;
	};
}
