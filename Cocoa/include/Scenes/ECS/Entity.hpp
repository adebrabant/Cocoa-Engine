#pragma once

#include <cstdint>

namespace Cocoa::Scenes
{
	class Entity
	{
	public:
		Entity(uint32_t id);
		~Entity() = default;
		uint32_t GetId() const { return m_id; }
		Entity& operator = (const Entity& other) = default;
		bool operator == (const Entity& other) const { return m_id == other.m_id; }
		bool operator != (const Entity& other) const { return m_id != other.m_id; }
		bool operator > (const Entity& other) const { return m_id > other.m_id; }
		bool operator < (const Entity& other) const { return m_id < other.m_id; }

	private:
		uint32_t m_id;
	};
}