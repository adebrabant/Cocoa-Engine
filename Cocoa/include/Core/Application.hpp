#pragma once

#include "Chronos/FrameClock.hpp"
#include "Assets/AssetPathProvider.hpp"
#include "Platforms/WindowProperties.hpp"

#include <string>
#include <memory>

namespace Cocoa::Graphics
{
	class Renderer2D;
	class OrthographicCamera;
}

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
		void FixedUpdate(Scenes::SceneManager& sceneManager, float fixedDeltaTime);
		void Update(Scenes::SceneManager& sceneManager, float deltaTime);
		void Render(Scenes::SceneManager& sceneManager, Graphics::Renderer2D& renderer, Graphics::OrthographicCamera& camera, float alpha);

		// ToDo: Need to come back to this
		virtual void ConfigureScenes(Scenes::SceneManager& sceneManager);

	private:
		Assets::AssetPathProvider m_assetPathProvider;
		Chronos::FrameClock m_frameClock;
		Platforms::WindowProperties m_windowProps;
	};
}