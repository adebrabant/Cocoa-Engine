#pragma once

#include "assets/AssetDatabase.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>

namespace cocoa::assets
{
	class JsonAssetDatabase : public AssetDatabase
	{
	public:
		explicit JsonAssetDatabase(std::filesystem::path  metadataPath);
		[[nodiscard]] const TextureRecord& getTextureInfo(const std::string& id) const override;
		[[nodiscard]] const ShaderRecord& getShaderInfo(const std::string& id) const override;
		[[nodiscard]] const MaterialRecord& getMaterialInfo(const std::string& id) const override;
		[[nodiscard]] const SpriteRecord& getSpriteInfo(const std::string& id) const override;

	private:
		void loadTextureRecords();
		void loadShaderRecords();
		void loadMaterialRecords();
		void loadSpriteRecords();

	private:
		const std::filesystem::path m_metadataPath;
		std::unordered_map<std::string, TextureRecord> m_textureRecords;
		std::unordered_map<std::string, ShaderRecord> m_shaderRecords;
		std::unordered_map<std::string, MaterialRecord> m_materialRecords;
		std::unordered_map<std::string, SpriteRecord> m_spriteRecords;
	};
}
