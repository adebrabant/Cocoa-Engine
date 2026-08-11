#pragma once

#include "Scenes/Scene.hpp"
#include "Core/Memory.hpp"
#include <vector>
#include <type_traits>

namespace Cocoa::Assets
{
	class ResourceLoader;
}

namespace Cocoa::Graphics
{
	class Renderer2D;
}

namespace Cocoa::Scenes
{
	class SceneManager
	{
	public:
		SceneManager(Assets::ResourceLoader& loader);
		~SceneManager() = default;
		[[nodiscard]] Scene* GetCurrentScene() const;
		void FixedUpdate(float fixedDeltaTime) const;
		void Update(float deltaTime) const;
		void Render(Graphics::Renderer2D& renderer, float alpha) const;
		template<typename TScene> void SetScene();
		template<typename TScene> void AddScene();
		template<typename TScene> TScene* GetScene();

	protected:
		template<typename TScene> constexpr void ValidateScene();

	private:
		std::vector<Unique<Scene>> m_scenes;
		Assets::ResourceLoader& m_resourceLoader;
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
			m_currentScene->Unload(m_resourceLoader);

		m_currentScene = newScene;

		if (m_currentScene)
			m_currentScene->Load(m_resourceLoader);
	}

	template<typename TScene>
	inline void SceneManager::AddScene()
	{
		ValidateScene<TScene>();

		if (GetScene<TScene>())
		{
			return;
		}

		m_scenes.emplace_back(CreateUnique<TScene>());
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