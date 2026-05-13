#pragma once

#include "Graphics/IWindow.hpp"
#include "Graphics/IRenderer.hpp"
#include "Graphics/GraphicsFactory.hpp"
#include "Scenes/SceneManager.hpp"
#include "Chronos/FrameClock.hpp"
#include "Assets/AssetManager.hpp"
#include "Assets/AssetPathProvider.hpp"

#include <string>
#include <memory>

namespace VexEngine::Graphics
{
	struct Pseudo3DRenderer;
}

namespace VexEngine
{
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title);
		void Run();

	protected:
		void Update(float deltaTime);
		void Render(float alpha);

	protected:
		Scenes::SceneManager m_sceneManager;

	private:
		Graphics::GraphicsFactory m_graphicsFactory;
		Assets::AssetPathProvider m_assetPathProvider;
		Assets::AssetManager m_assetManager;
		std::unique_ptr<Graphics::IWindow> m_window;
		std::unique_ptr<Graphics::IRenderer> m_renderer;
		Chronos::FrameClock m_frameClock;
	};
}