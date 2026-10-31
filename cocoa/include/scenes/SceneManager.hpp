#pragma once

#include "scenes/Scene.hpp"
#include "utilities/Memory.hpp"

#include <vector>
#include <type_traits>

namespace cocoa::assets
{
	class ResourceLoader;
}

namespace cocoa::graphics
{
	class Renderer2D;
}

namespace cocoa::scenes
{
	class SceneManager
	{
	public:
		explicit SceneManager(assets::ResourceLoader& loader);
		~SceneManager() = default;
		[[nodiscard]] Scene* getCurrentScene() const;
		void fixedUpdate(float fixedDeltaTime) const;
		void update(float deltaTime) const;
		void render(graphics::Renderer2D& renderer, float alpha) const;
		template<typename TScene> void setScene();
		template<typename TScene> void addScene();
		template<typename TScene> TScene* getScene();

	protected:
		template<typename TScene> constexpr void validateScene() const;

	private:
		std::vector<Unique<Scene>> m_scenes;
		assets::ResourceLoader& m_resourceLoader;
		Scene* m_currentScene = nullptr;
	};

	template<typename TScene>
	inline void SceneManager::setScene()
	{
		auto newScene = getScene<TScene>();
		if (!newScene)
		{
			addScene<TScene>();
			newScene = getScene<TScene>();
		}

		if (m_currentScene == newScene)
			return;

		if (m_currentScene)
			m_currentScene->unload(m_resourceLoader);

		m_currentScene = newScene;

		if (m_currentScene)
			m_currentScene->load(m_resourceLoader);
	}

	template<typename TScene>
	inline void SceneManager::addScene()
	{
		validateScene<TScene>();

		if (getScene<TScene>())
		{
			return;
		}

		m_scenes.emplace_back(createUnique<TScene>());
	}

	template<typename TScene>
	inline TScene* SceneManager::getScene()
	{
		validateScene<TScene>();
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
	constexpr void SceneManager::validateScene() const
	{
		static_assert(std::is_base_of_v<Scene, TScene>,
			"TScene must derive from Scene");
	}
}
