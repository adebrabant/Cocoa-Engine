#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include <unordered_map>

namespace cocoa::scenes
{
	// ToDo: remove I Prefix
	class IComponentStorage
	{
	public:
		virtual ~IComponentStorage() = default;
		virtual void entityDestroyed(uint32_t entityId) = 0;
	};

	template<typename TComponent>
	class ComponentStorage : public IComponentStorage
	{

	public:
		void add(uint32_t entity, const TComponent& component)
		{
			size_t newIndex = m_components.size();
			m_components.emplace_back(component);
			m_entities.emplace_back(entity);
			m_entityToIndex[entity] = newIndex;
		}

		void remove(uint32_t entity)
		{
			size_t index = m_entityToIndex[entity];
			size_t lastIndex = m_components.size() - 1;

			m_components[index] = std::move(m_components[lastIndex]);
			m_entities[index] = m_entities[lastIndex];
			m_entityToIndex[m_entities[index]] = index;

			m_components.pop_back();
			m_entities.pop_back();
			m_entityToIndex.erase(entity);
		}

		TComponent& get(uint32_t entity)
		{
			return m_components[m_entityToIndex[entity]];
		}

		bool has(uint32_t entity) const
		{
			return m_entityToIndex.find(entity) != m_entityToIndex.end();
		}

		size_t size() const
		{
			return m_components.size();
		}

		uint32_t getEntity(size_t index) const
		{
			return m_entities[index];
		}

		void entityDestroyed(uint32_t entityId) override
		{
			if (m_entityToIndex.find(entityId) != m_entityToIndex.end())
			{
				remove(entityId);
			}
		}

	private:
		std::vector<TComponent> m_components;
		std::vector<uint32_t> m_entities;
		std::unordered_map<uint32_t, size_t> m_entityToIndex;
	};
}
