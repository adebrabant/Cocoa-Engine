#include "Scenes/SceneManager.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Scenes/Scene.hpp"

namespace VexEngine::Scenes
{
	Scene* SceneManager::GetCurrentScene()
	{
		return m_currentScene;
	}

	void SceneManager::FixedUpdate(float fixedDeltaTime)
	{
		// ToDo: Handle when physics is ready
	}

	void SceneManager::Update(float deltaTime)
	{
		if (m_currentScene)
		{
			m_currentScene->Update(deltaTime);
		}
	}

	void SceneManager::Render(Graphics::Renderer2D& renderer, float alpha)
	{
		if (m_currentScene)
		{
			m_currentScene->Render(renderer, alpha);
		}
	}
}