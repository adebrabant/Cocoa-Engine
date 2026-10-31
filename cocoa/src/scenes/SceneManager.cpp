#include "scenes/SceneManager.hpp"
#include "assets/ResourceLoader.hpp"
#include "graphics/Renderer2D.hpp"
#include "scenes/Scene.hpp"

namespace cocoa::scenes
{
	SceneManager::SceneManager(assets::ResourceLoader& loader) :
		m_resourceLoader(loader)
	{

	}

	Scene* SceneManager::getCurrentScene() const
	{
		return m_currentScene;
	}

	void SceneManager::fixedUpdate(float fixedDeltaTime) const
	{
		// ToDo: Handle when physics is ready
	}

	void SceneManager::update(float deltaTime) const
	{
		if (m_currentScene)
		{
			m_currentScene->update(deltaTime);
		}
	}

	void SceneManager::render(graphics::Renderer2D& renderer, const float alpha) const
	{
		if (m_currentScene)
		{
			m_currentScene->render(renderer, alpha);
		}
	}
}
