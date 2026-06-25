#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include <unordered_map>

namespace Cocoa::Scenes
{
	// ToDo: Remove I Prefix
	class IComponentStorage
	{
	public:
		virtual ~IComponentStorage() = default;
		virtual void EntityDestroyed(uint32_t entityId) = 0;
	};

	template<typename TComponent>
	class ComponentStorage : public IComponentStorage
	{

	public:
		void Add(uint32_t entity, const TComponent& component)
		{
			size_t newIndex = m_components.size();
			m_components.emplace_back(component);
			m_entities.emplace_back(entity);
			m_entityToIndex[entity] = newIndex;
		}

		void Remove(uint32_t entity)
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

		TComponent& Get(uint32_t entity)
		{
			return m_components[m_entityToIndex[entity]];
		}

		bool Has(uint32_t entity) const
		{
			return m_entityToIndex.find(entity) != m_entityToIndex.end();
		}

		size_t Size() const
		{
			return m_components.size();
		}

		uint32_t GetEntity(size_t index) const
		{
			return m_entities[index];
		}

		void EntityDestroyed(uint32_t entityId) override
		{
			if (m_entityToIndex.find(entityId) != m_entityToIndex.end())
			{
				Remove(entityId);
			}
		}

	private:
		std::vector<TComponent> m_components;
		std::vector<uint32_t> m_entities;
		std::unordered_map<uint32_t, size_t> m_entityToIndex;
	};
}