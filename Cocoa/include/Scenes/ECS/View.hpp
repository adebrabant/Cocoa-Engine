#pragma once

#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/ComponentStorage.hpp"
#include "Scenes/ECS/Entity.hpp"

#include <cstdint>
#include <tuple>
#include <utility>

namespace Cocoa::Scenes
{
	template<typename... TComponents>
	class View
	{
	public:
		View(World& world) : m_world(world)
		{
			m_componentStorages = std::make_tuple(m_world.GetComponentStorage<TComponents>()...);
			m_primaryStorage = std::get<0>(m_componentStorages);
		}

		class Iterator
		{
		public:
			Iterator(View* view, size_t index) : m_view(view), m_index(index)
			{
				SkipInvalid();
			}

			bool operator!=(const Iterator& other) const
			{
				return m_index != other.m_index;
			}

			Iterator& operator++()
			{
				++m_index;
				SkipInvalid();
				return *this;
			}

			auto operator*()
			{
				uint32_t entityId = m_view->m_primaryStorage->GetEntity(m_index);

				return std::tuple<TComponents&...>(
					m_view->m_world.GetComponent<TComponents>(Entity(entityId))...
				);
			}

		private:
			void SkipInvalid()
			{
				if (!m_view->m_primaryStorage)
				{
					m_index = 0; 
					return;
				}

				while (m_index < m_view->m_primaryStorage->Size())
				{
					uint32_t entityId = m_view->m_primaryStorage->GetEntity(m_index);
					bool valid = true;
					std::apply([&](auto*... storage)
						{
							((valid &= storage && storage->Has(entityId)), ...);
						}, m_view->m_componentStorages);

					if (valid)
						break;

					++m_index;
				}
			}
			
		private:
			View* m_view;
			size_t m_index;
		};

		Iterator begin()
		{
			if (!m_primaryStorage)
				return end();

			return Iterator(this, 0);
		}

		Iterator end()
		{
			return Iterator(this, m_primaryStorage ? m_primaryStorage->Size() : 0);
		}

	private:
		World& m_world;
		std::tuple<ComponentStorage<TComponents>*...> m_componentStorages;
		ComponentStorage<std::tuple_element_t<0, std::tuple<TComponents...>>>* m_primaryStorage;
	};
}