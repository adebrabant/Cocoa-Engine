#pragma once

#include <cstdint>

namespace cocoa::scenes
{
	class Entity
	{
	public:
        explicit Entity(uint32_t id);
		~Entity() = default;
		[[nodiscard]] uint32_t getId() const { return m_id; }
		Entity& operator = (const Entity& other) = default;
		bool operator == (const Entity& other) const { return m_id == other.m_id; }
		bool operator != (const Entity& other) const { return m_id != other.m_id; }
		bool operator > (const Entity& other) const { return m_id > other.m_id; }
		bool operator < (const Entity& other) const { return m_id < other.m_id; }

	private:
		uint32_t m_id;
	};
}
