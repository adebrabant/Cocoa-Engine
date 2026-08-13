#pragma once

#include "Chronos/FrameClock.hpp"
#include "Assets/AssetPathProvider.hpp"
#include "Platforms/WindowProperties.hpp"
#include "Graphics/Viewport.hpp"
#include "Events/EventBus.hpp"
#include "Core/Memory.hpp"

#include <string>

namespace Cocoa::Scenes
{
	class SceneManager;
}

namespace Cocoa::Graphics
{
	class GraphicsDevice;
}

namespace Cocoa::Core
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
		Graphics::Viewport m_viewport;
		Events::EventBus m_eventBus;
		Unique<Graphics::GraphicsDevice> m_graphicsDevice;
		Events::EventBus::SubscriptionToken m_FramebufferResizeEventToken;
	};
}