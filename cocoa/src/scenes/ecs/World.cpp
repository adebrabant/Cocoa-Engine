#include "scenes/ecs/World.hpp"
#include "graphics/Renderer2D.hpp"
#include "scenes/ecs/Entity.hpp"
#include "scenes/systems/System.hpp"

#include <cstdint>

namespace cocoa::scenes
{
	World::World() :
		m_nextEntityId(0),
		m_freeEntityIds(),
		m_activeEntities(),
		m_componentStorages(),
		m_systems()
	{

	}

	void World::update(float deltaTime)
	{
		for (auto& system : m_systems)
		{
			system->update(*this, deltaTime);
		}
	}

	void World::beforeRender(graphics::Renderer2D& renderer, float alpha)
	{
		for (auto& system : m_systems)
		{
			system->beginRender(*this, renderer, alpha);
		}
	}

	void World::render(graphics::Renderer2D& renderer, float alpha)
	{
		for (auto& system : m_systems)
		{
			system->render(*this, renderer, alpha);
		}
	}

	Entity World::createEntity()
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

	void World::destroyEntity(const Entity& entity)
	{
		uint32_t entityId = entity.getId();
		auto it = m_activeEntities.find(entityId);
		if (it != m_activeEntities.end())
		{
			m_activeEntities.erase(it);
			m_freeEntityIds.emplace_back(entityId);
		}
	}
}
