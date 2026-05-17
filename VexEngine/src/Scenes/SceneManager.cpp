#include "Scenes/SceneManager.hpp"
#include "Graphics/IRenderer.hpp"
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

	void SceneManager::Render(Graphics::IRenderer& renderer, float alpha)
	{
		if (m_currentScene)
		{
			m_currentScene->Render(renderer, alpha);
		}
	}
}