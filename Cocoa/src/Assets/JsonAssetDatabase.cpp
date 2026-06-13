#include "Assets/JsonAssetDatabase.hpp"

#include <fstream>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace Cocoa::Assets
{
	JsonAssetDatabase::JsonAssetDatabase(const std::filesystem::path& metadataPath) :
		m_metadataPath(metadataPath),
		m_textureRecords()
	{
		LoadTextureRecords();
	}

	const TextureRecord& JsonAssetDatabase::GetTextureInfo(const std::string& id) const
	{
		auto it = m_textureRecords.find(id);

		if (it == m_textureRecords.end())
		{
			throw std::runtime_error(
				"No Texture records found with the texture id: " +
				id
			);
		}

		return it->second;
	}

	void JsonAssetDatabase::LoadTextureRecords()
	{
		auto texturesPath = m_metadataPath / "textures.json";
		std::ifstream file(texturesPath);
		if (!file)
		{
			throw std::runtime_error("Failed to open texture metadata file: " +
				texturesPath.string()
			);
		}

		nlohmann::json data = nlohmann::json::parse(file);

		for (auto& [id, textureJson] : data.items())
		{
			TextureRecord record
			{
				.Id = id,
				.Path = textureJson.at("path").get<std::string>(),
				.Format = textureJson.at("format").get<std::string>(),
				.MinFilter = textureJson.at("minFilter").get<std::string>(),
				.MagFilter = textureJson.at("magFilter").get<std::string>(),
				.WrapS = textureJson.at("wrapS").get<std::string>(),
				.WrapT = textureJson.at("wrapT").get<std::string>(),
				.GenerateMipmaps = textureJson.at("generateMipmaps").get<bool>()
			};

			m_textureRecords[id] = record;
		}
	}
}