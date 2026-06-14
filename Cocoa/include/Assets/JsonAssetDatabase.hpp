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
		const ShaderRecord& GetShaderInfo(const std::string& id) const override;
		const MaterialRecord& GetMaterialInfo(const std::string& id) const override;

	private:
		void LoadTextureRecords();
		void LoadShaderRecords();
		void LoadMaterialRecords();

	private:
		const std::filesystem::path m_metadataPath;
		std::unordered_map<std::string, TextureRecord> m_textureRecords;
		std::unordered_map<std::string, ShaderRecord> m_shaderRecords;
		std::unordered_map<std::string, MaterialRecord> m_materialRecords;
	};
}