#pragma once

#include "Assets/AssetDatabase.hpp"

#include <string>
#include <filesystem>
#include <unordered_map>

namespace Cocoa::Assets
{
	class JsonAssetDatabase : public AssetDatabase
	{
	public:
		JsonAssetDatabase(const std::filesystem::path& metadataPath);
		const TextureRecord& GetTextureInfo(const std::string& id) const override;

	private:
		void LoadTextureRecords();

	private:
		const std::filesystem::path m_metadataPath;
		std::unordered_map<std::string, TextureRecord> m_textureRecords;
	};
}