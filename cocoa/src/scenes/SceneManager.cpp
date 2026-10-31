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

	Scene* SceneManager::GetCurrentScene() const
	{
		return m_currentScene;
	}

	void SceneManager::FixedUpdate(float fixedDeltaTime) const
	{
		// ToDo: Handle when physics is ready
	}

	void SceneManager::Update(float deltaTime) const
	{
		if (m_currentScene)
		{
			m_currentScene->Update(deltaTime);
		}
	}

	void SceneManager::Render(graphics::Renderer2D& renderer, const float alpha) const
	{
		if (m_currentScene)
		{
			m_currentScene->Render(renderer, alpha);
		}
	}
}
