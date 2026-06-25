#pragma once

#include "Graphics/Renderer2D.hpp"
#include "Scenes/ECS/Entity.hpp"
#include "Scenes/ECS/ComponentStorage.hpp"
#include "Scenes/ECS/ComponentType.hpp"
#include "Scenes/Systems/System.hpp"
#include <cstdint>
#include <vector>
#include <set>
#include <unordered_map>

// ToDo: Remove for Memory.hpp
#include <memory>

namespace Cocoa::Scenes
{
	class World
	{
	public:
		World();
		~World() = default;
		void Update(float deltaTime);
		void Render(Graphics::Renderer2D& renderer, float alpha);
		Entity CreateEntity();
		void DestroyEntity(const Entity& entity);

		template<typename TComponent> 
		void AddComponent(Entity entity, const TComponent& component);

		template<typename TComponent> 
		TComponent& GetComponent(Entity entity);

		template<typename TComponent> 
		void RemoveComponent(Entity entity);

		template<typename TCompoent> 
		ComponentStorage<TCompoent>* GetComponentStorage();

		template<typename TSystem, typename... TArgs>
		requires std::derived_from<TSystem, System>
		TSystem& AddSystem(TArgs&&... args);

	private:
		uint32_t m_nextEntityId;
		std::vector<uint32_t> m_freeEntityIds;
		std::set<uint32_t> m_activeEntities;
		std::unordered_map<uint32_t, std::shared_ptr<IComponentStorage>> m_componentStorages;
		std::vector<std::unique_ptr<System>> m_systems;
	};

	template<typename TComponent>
	inline void World::AddComponent(Entity entity, const TComponent& component)
	{
		uint32_t typeId = ComponentType<TComponent>::GetId();
		if (m_componentStorages.find(typeId) == m_componentStorages.end())
		{
			m_componentStorages[typeId] = std::make_shared<ComponentStorage<TComponent>>();
		}

		auto componentStorage = std::static_pointer_cast<ComponentStorage<TComponent>>(m_componentStorages[typeId]);
		componentStorage->Add(entity.GetId(), component);
	}

	template<typename TComponent>
	inline TComponent& World::GetComponent(Entity entity)
	{
		uint32_t typeId = ComponentType<TComponent>::GetId();
		auto componentStorage = std::static_pointer_cast<ComponentStorage<TComponent>>(m_componentStorages[typeId]);
		return componentStorage->Get(entity.GetId());
	}

	template<typename TComponent>
	inline void World::RemoveComponent(Entity entity)
	{
		uint32_t typeId = ComponentType<TComponent>::GetId();
		auto componentStorage = std::static_pointer_cast<ComponentStorage<TComponent>>(m_componentStorages[typeId]);
		componentStorage->Remove(entity.GetId());
	}

	template<typename TComponent>
	inline ComponentStorage<TComponent>* World::GetComponentStorage()
	{
		uint32_t typeId = ComponentType<TComponent>::GetId();

		auto it = m_componentStorages.find(typeId);
		if (it == m_componentStorages.end())
			return nullptr;

		return static_cast<ComponentStorage<TComponent>*>(it->second.get());
	}

	template<typename TSystem, typename... TArgs> 
		requires std::derived_from<TSystem, System>
	inline TSystem& World::AddSystem(TArgs&&... args)
	{
		auto system = std::make_unique<TSystem>(std::forward<TArgs>(args)...);
		TSystem& reference = *system;
		m_systems.emplace_back(std::move(system));
		return reference;
	}
}