#pragma once

#include <cstdint>

namespace VexEngine::Assets
{
	enum class AssetType
	{
		None,
		Texture,
		Sound,
		Font
	};

	class Asset
	{
	public:
		Asset(uint32_t id, AssetType type);
		uint32_t GetId() const { return m_id; }
		AssetType GetType() const { return m_type; }
		bool IsValid() const;
		bool operator==(const Asset&) const = default;

	private:
		uint32_t m_id;
		AssetType m_type;
	};
}