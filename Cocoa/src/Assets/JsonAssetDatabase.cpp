#include "Assets/JsonAssetDatabase.hpp"

#include <fstream>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace Cocoa::Assets
{
	JsonAssetDatabase::JsonAssetDatabase(const std::filesystem::path& metadataPath) :
		m_metadataPath(metadataPath),
		m_textureRecords(),
		m_shaderRecords(),
		m_materialRecords(),
		m_spriteRecords()
	{
		LoadTextureRecords();
		LoadShaderRecords();
		LoadMaterialRecords();
		LoadSpriteRecords();
	}

	const TextureRecord& JsonAssetDatabase::GetTextureInfo(const std::string& id) const
	{
		const auto it = m_textureRecords.find(id);

		if (it == m_textureRecords.end())
		{
			throw std::runtime_error(
				"No Texture records found with the texture id: " +
				id
			);
		}

		return it->second;
	}

	const ShaderRecord& JsonAssetDatabase::GetShaderInfo(const std::string& id) const
	{
		const auto it = m_shaderRecords.find(id);

		if (it == m_shaderRecords.end())
		{
			throw std::runtime_error(
				"No Shader records found with the texture id: " +
				id
			);
		}

		return it->second;
	}

	const MaterialRecord& JsonAssetDatabase::GetMaterialInfo(const std::string& id) const
	{
		const auto it = m_materialRecords.find(id);

		if (it == m_materialRecords.end())
		{
			throw std::runtime_error(
				"No Material records found with the texture id: " +
				id
			);
		}

		return it->second;
	}

	const SpriteRecord & JsonAssetDatabase::GetSpriteInfo(const std::string& id) const
	{
		const auto it = m_spriteRecords.find(id);

		if (it == m_spriteRecords.end())
		{
			throw std::runtime_error(
				"No Sprite records found with the sprite id:" +
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

	void JsonAssetDatabase::LoadShaderRecords()
	{
		auto shadersPath = m_metadataPath / "shaders.json";
		std::ifstream file(shadersPath);
		if (!file)
		{
			throw std::runtime_error("Failed to open shaders metadata file: " +
				shadersPath.string()
			);
		}

		nlohmann::json data = nlohmann::json::parse(file);

		for (auto& [id, shaderJson] : data.items())
		{
			ShaderRecord record
			{
				.Id = id,
				.VertexPath = shaderJson.at("vertexPath").get<std::string>(),
				.FragmentPath = shaderJson.at("fragmentPath").get<std::string>(),
			};

			m_shaderRecords[id] = record;
		}
	}

	void JsonAssetDatabase::LoadMaterialRecords()
	{
		auto materialsPath = m_metadataPath / "materials.json";
		std::ifstream file(materialsPath);
		if (!file)
		{
			throw std::runtime_error("Failed to open materials metadata file: " +
				materialsPath.string()
			);
		}

		nlohmann::json data = nlohmann::json::parse(file);

		for (auto& [id, materialJson] : data.items())
		{
			MaterialRecord record
			{
				.Id = id,
				.ShaderId = materialJson.at("shader").get<std::string>(),
				.TextureId = materialJson.at("texture").get<std::string>(),
				.Tint = Core::Color
				{
					materialJson.at("tint").at(0).get<float>(),
					materialJson.at("tint").at(1).get<float>(),
					materialJson.at("tint").at(2).get<float>(),
					materialJson.at("tint").at(3).get<float>()
				}
			};

			m_materialRecords[id] = record;
		}
	}

	void JsonAssetDatabase::LoadSpriteRecords()
	{
		auto spritesPath = m_metadataPath / "sprites.json";
		std::ifstream file(spritesPath);
		if (!file)
		{
			throw std::runtime_error("Failed to open sprites metadata file: " +
				spritesPath.string()
			);
		}

		nlohmann::json data = nlohmann::json::parse(file);

		for (auto& [id, spriteJson] : data.items())
		{
			SpriteRecord record
			{
				.Id = id,
				.TextureId = spriteJson.at("texture").get<std::string>(),
				.MinUV = Math::Vector2f
				{
					spriteJson.at("minUV").at(0).get<float>(),
					spriteJson.at("minUV").at(1).get<float>()
				},
				.MaxUV = Math::Vector2f
				{
					spriteJson.at("maxUV").at(0).get<float>(),
					spriteJson.at("maxUV").at(1).get<float>()
				}
			};

			m_spriteRecords[id] = record;
		}
	}
}
