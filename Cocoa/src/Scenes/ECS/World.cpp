#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/Entity.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Scenes/Systems/System.hpp"

#include <cstdint>

namespace Cocoa::Scenes
{
	World::World() :
		m_nextEntityId(0),
		m_freeEntityIds(),
		m_activeEntities(),
		m_componentStorages(),
		m_systems()
	{

	}

	void World::Update(float deltaTime)
	{
		for (auto& system : m_systems)
		{
			system.get()->Update(*this, deltaTime);
		}
	}

	void World::Render(Graphics::Renderer2D& renderer, float alpha)
	{ 
		for (auto& system : m_systems)
		{
			system.get()->Render(*this, renderer, alpha);
		}
	}

	Entity World::CreateEntity()
	{
		uint32_t entityId;
		if (!m_freeEntityIds.empty())
		{
			entityId = m_freeEntityIds.back();
			m_freeEntityIds.emplace_back();
		}
		else
		{
			entityId = m_nextEntityId++;
		}

		m_activeEntities.insert(entityId);

		return Entity(entityId);
	}

	void World::DestroyEntity(const Entity& entity)
	{
		uint32_t entityId = entity.GetId();
		auto it = m_activeEntities.find(entityId);
		if (it != m_activeEntities.end())
		{
			m_activeEntities.erase(it);
			m_freeEntityIds.emplace_back(entityId);
		}
	}
}