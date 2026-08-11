#include "Scenes/SceneManager.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Assets/ResourceLoader.hpp"
#include "Scenes/Scene.hpp"

namespace Cocoa::Scenes
{
	SceneManager::SceneManager(Assets::ResourceLoader& loader) 
		: m_resourceLoader(loader)
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

	void SceneManager::Render(Graphics::Renderer2D& renderer, const float alpha) const
	{
		if (m_currentScene)
		{
			m_currentScene->Render(renderer, alpha);
		}
	}
}