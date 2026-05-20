#pragma once

#include "Scenes/Scene.hpp"
#include "Graphics/Renderer2D.hpp"
#include <vector>
#include <memory>
#include <type_traits>

namespace VexEngine::Scenes
{
	class SceneManager
	{
	public:
		SceneManager() = default;
		~SceneManager() = default;
		Scene* GetCurrentScene();
		void FixedUpdate(float fixedDeltaTime);
		void Update(float deltaTime);
		void Render(Graphics::Renderer2D& renderer, float alpha);
		template<typename TScene> void SetScene();
		template<typename TScene> void AddScene();
		template<typename TScene> TScene* GetScene();

	protected:
		template<typename TScene> constexpr void ValidateScene();

	private:
		std::vector<std::unique_ptr<Scene>> m_scenes;
		Scene* m_currentScene = nullptr;
	};

	template<typename TScene>
	inline void SceneManager::SetScene()
	{
		auto newScene = GetScene<TScene>();
		if (!newScene)
		{
			AddScene<TScene>();
			newScene = GetScene<TScene>();
		}

		if (m_currentScene == newScene)
			return;

		if (m_currentScene)
			m_currentScene->Unload();

		m_currentScene = newScene;

		if (m_currentScene)
			m_currentScene->Load();
	}

	template<typename TScene>
	inline void SceneManager::AddScene()
	{
		ValidateScene<TScene>();

		if (GetScene<TScene>())
		{
			return;
		}

		m_scenes.emplace_back(std::make_unique<TScene>());
	}

	template<typename TScene>
	inline TScene* SceneManager::GetScene()
	{
		ValidateScene<TScene>();
		for (const auto& scene : m_scenes)
		{
			if (auto casted = dynamic_cast<TScene*>(scene.get()))
			{
				return casted;
			}
		}

		return nullptr;
	}

	template<typename TScene>
	constexpr void SceneManager::ValidateScene()
	{
		static_assert(std::is_base_of_v<Scene, TScene>,
			"TScene must derive from Scene");
	}
}