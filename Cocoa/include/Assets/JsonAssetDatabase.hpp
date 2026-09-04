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
		explicit JsonAssetDatabase(const std::filesystem::path& metadataPath);
		[[nodiscard]] const TextureRecord& GetTextureInfo(const std::string& id) const override;
		[[nodiscard]] const ShaderRecord& GetShaderInfo(const std::string& id) const override;
		[[nodiscard]] const MaterialRecord& GetMaterialInfo(const std::string& id) const override;
		[[nodiscard]] const SpriteRecord& GetSpriteInfo(const std::string& id) const override;

	private:
		void LoadTextureRecords();
		void LoadShaderRecords();
		void LoadMaterialRecords();
		void LoadSpriteRecords();

	private:
		const std::filesystem::path m_metadataPath;
		std::unordered_map<std::string, TextureRecord> m_textureRecords;
		std::unordered_map<std::string, ShaderRecord> m_shaderRecords;
		std::unordered_map<std::string, MaterialRecord> m_materialRecords;
		std::unordered_map<std::string, SpriteRecord> m_spriteRecords;
	};
}