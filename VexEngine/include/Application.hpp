#pragma once

#include "Platforms/IWindow.hpp"
#include "Scenes/SceneManager.hpp"
#include "Chronos/FrameClock.hpp"
#include "Assets/AssetManager.hpp"
#include "Assets/AssetPathProvider.hpp"
#include "Platforms/WindowProperties.hpp"

#include <string>
#include <memory>

namespace VexEngine
{
	class Application
	{
	public:
		Application(uint32_t windowWidth, uint32_t windowHeight, const std::string& title);
		void Run();

	protected:
		void FixedUpdate(float fixedDeltaTime);
		void Update(float deltaTime);
		void Render(float alpha);

	protected:
		Scenes::SceneManager m_sceneManager;

	private:
		std::unique_ptr<Platforms::IWindow> m_window;
		Assets::AssetPathProvider m_assetPathProvider;
		Assets::AssetManager m_assetManager;
		Chronos::FrameClock m_frameClock;
		Platforms::WindowProperties m_windowProps;
	};
}