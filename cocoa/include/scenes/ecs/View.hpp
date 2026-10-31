#pragma once

#include "scenes/ecs/ComponentStorage.hpp"
#include "scenes/ecs/Entity.hpp"
#include "scenes/ecs/World.hpp"

#include <cstdint>
#include <tuple>
#include <utility>

namespace cocoa::scenes
{
	template<typename... TComponents>
	class View
	{
	public:
        explicit View(World& world) : m_world(world)
		{
			m_componentStorages = std::make_tuple(m_world.getComponentStorage<TComponents>()...);
			m_primaryStorage = std::get<0>(m_componentStorages);
		}

		class Iterator
		{
		public:
			Iterator(View* view, size_t index) : m_view(view), m_index(index)
			{
				skipInvalid();
			}

			bool operator!=(const Iterator& other) const
			{
				return m_index != other.m_index;
			}

			Iterator& operator++()
			{
				++m_index;
				skipInvalid();
				return *this;
			}

			auto operator*()
			{
				uint32_t entityId = m_view->m_primaryStorage->getEntity(m_index);

				return std::tuple<TComponents&...>(
					m_view->m_world.getComponent<TComponents>(Entity(entityId))...
				);
			}

		private:
			void skipInvalid()
			{
				if (!m_view->m_primaryStorage)
				{
					m_index = 0;
					return;
				}

				while (m_index < m_view->m_primaryStorage->size())
				{
					uint32_t entityId = m_view->m_primaryStorage->getEntity(m_index);
					bool valid = true;
					std::apply([&](auto*... storage)
						{
							((valid &= storage && storage->has(entityId)), ...);
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
			return Iterator(this, m_primaryStorage ? m_primaryStorage->size() : 0);
		}

	private:
		World& m_world;
		std::tuple<ComponentStorage<TComponents>*...> m_componentStorages;
		ComponentStorage<std::tuple_element_t<0, std::tuple<TComponents...>>>* m_primaryStorage;
	};
}
