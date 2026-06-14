#pragma once

#include "Scenes/SceneManager.hpp"
#include "Chronos/FrameClock.hpp"
#include "Assets/AssetPathProvider.hpp"
#include "Platforms/WindowProperties.hpp"

#include <string>
#include <memory>

namespace Cocoa::Graphics
{
	class Renderer2D;
}

namespace Cocoa::Core
{

	class Application
	{
	public:
		Application(uint32_t windowWidth, uint32_t windowHeight, const std::string& title);
		void Run();

	protected:
		void FixedUpdate(float fixedDeltaTime);
		void Update(float deltaTime);
		void Render(Graphics::Renderer2D& renderer, float alpha);

	protected:
		Scenes::SceneManager m_sceneManager;

	private:
		Assets::AssetPathProvider m_assetPathProvider;
		Chronos::FrameClock m_frameClock;
		Platforms::WindowProperties m_windowProps;
	};
}