#pragma once

#include "graphics/Renderer2D.hpp"
#include "scenes/ecs/ComponentStorage.hpp"
#include "scenes/ecs/ComponentType.hpp"
#include "scenes/ecs/Entity.hpp"
#include "scenes/systems/System.hpp"
#include <cstdint>
#include <set>
#include <unordered_map>
#include <vector>

// ToDo: remove for Memory.hpp
#include <memory>

namespace cocoa::scenes
{
	class World
	{
	public:
		World();
		~World() = default;
		void update(float deltaTime);
		void beforeRender(graphics::Renderer2D& renderer, float alpha);
		void render(graphics::Renderer2D& renderer, float alpha);
		Entity createEntity();
		void destroyEntity(const Entity& entity);

		template<typename TComponent>
		void addComponent(Entity entity, const TComponent& component);

		template<typename TComponent>
		TComponent& getComponent(Entity entity);

		template<typename TComponent>
		void removeComponent(Entity entity);

		template<typename TCompoent>
		ComponentStorage<TCompoent>* getComponentStorage();

		template<typename TSystem, typename... TArgs>
		requires std::derived_from<TSystem, System>
		TSystem& addSystem(TArgs&&... args);

	private:
		uint32_t m_nextEntityId;
		std::vector<uint32_t> m_freeEntityIds;
		std::set<uint32_t> m_activeEntities;
		std::unordered_map<uint32_t, std::shared_ptr<IComponentStorage>> m_componentStorages;
		std::vector<std::unique_ptr<System>> m_systems;
	};

	template<typename TComponent>
	inline void World::addComponent(Entity entity, const TComponent& component)
	{
		uint32_t typeId = ComponentType<TComponent>::getId();
		if (m_componentStorages.find(typeId) == m_componentStorages.end())
		{
			m_componentStorages[typeId] = std::make_shared<ComponentStorage<TComponent>>();
		}

		auto componentStorage = std::static_pointer_cast<ComponentStorage<TComponent>>(m_componentStorages[typeId]);
		componentStorage->add(entity.getId(), component);
	}

	template<typename TComponent>
	inline TComponent& World::getComponent(Entity entity)
	{
		uint32_t typeId = ComponentType<TComponent>::getId();
		auto componentStorage = std::static_pointer_cast<ComponentStorage<TComponent>>(m_componentStorages[typeId]);
		return componentStorage->get(entity.getId());
	}

	template<typename TComponent>
	inline void World::removeComponent(Entity entity)
	{
		uint32_t typeId = ComponentType<TComponent>::getId();
		auto componentStorage = std::static_pointer_cast<ComponentStorage<TComponent>>(m_componentStorages[typeId]);
		componentStorage->remove(entity.getId());
	}

	template<typename TComponent>
	inline ComponentStorage<TComponent>* World::getComponentStorage()
	{
		uint32_t typeId = ComponentType<TComponent>::getId();

		auto it = m_componentStorages.find(typeId);
		if (it == m_componentStorages.end())
			return nullptr;

		return static_cast<ComponentStorage<TComponent>*>(it->second.get());
	}

	template<typename TSystem, typename... TArgs>
		requires std::derived_from<TSystem, System>
	inline TSystem& World::addSystem(TArgs&&... args)
	{
		auto system = std::make_unique<TSystem>(std::forward<TArgs>(args)...);
		TSystem& reference = *system;
		m_systems.emplace_back(std::move(system));
		return reference;
	}
}
