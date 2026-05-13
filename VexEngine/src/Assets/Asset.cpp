#include "Assets/Asset.hpp"
#include <cstdint>

namespace VexEngine::Assets
{
	Asset::Asset(uint32_t id, AssetType type) :
		m_id(id),
		m_type(type)
	{

	}

	bool Asset::IsValid() const
	{
		return m_id != 0 && m_type != AssetType::None;
	}
}