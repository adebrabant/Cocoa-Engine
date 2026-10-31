#include "assets/JsonAssetDatabase.hpp"
#include "utilities/Threading.hpp"

#include <array>
#include <exception>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <utility>

namespace cocoa::assets
{
	JsonAssetDatabase::JsonAssetDatabase(std::filesystem::path  metadataPath) :
		m_metadataPath(std::move(metadataPath)),
		m_textureRecords(),
		m_shaderRecords(),
		m_materialRecords(),
		m_spriteRecords()
	{
		std::array<std::exception_ptr, 4> errors;
		std::thread textureWorker;
		std::thread shaderWorker;
		std::thread materialWorker;
		std::thread spriteWorker;

		try
		{
			textureWorker = startThread(
				[this]{loadTextureRecords();},
				errors[0]
			);

			shaderWorker = startThread(
				[this]{loadShaderRecords();},
				errors[1]
			);

			materialWorker = startThread(
				[this]{loadMaterialRecords();},
				errors[2]
			);

			spriteWorker = startThread(
				[this]{loadSpriteRecords();},
				errors[3]
			);
		}
		catch (...)
		{
			safeJoin(textureWorker);
			safeJoin(shaderWorker);
			safeJoin(materialWorker);
			safeJoin(spriteWorker);
			throw;
		}

		safeJoin(textureWorker);
		safeJoin(shaderWorker);
		safeJoin(materialWorker);
		safeJoin(spriteWorker);

		for (const std::exception_ptr& error : errors)
		{
			if (error)
			{
				std::rethrow_exception(error);
			}
		}
	}

	const TextureRecord& JsonAssetDatabase::getTextureInfo(const std::string& id) const
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

	const ShaderRecord& JsonAssetDatabase::getShaderInfo(const std::string& id) const
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

	const MaterialRecord& JsonAssetDatabase::getMaterialInfo(const std::string& id) const
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

	const SpriteRecord& JsonAssetDatabase::getSpriteInfo(const std::string& id) const
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

	void JsonAssetDatabase::loadTextureRecords()
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
				.id = id,
				.path = textureJson.at("path").get<std::string>(),
				.format = textureJson.at("format").get<std::string>(),
				.minFilter = textureJson.at("minFilter").get<std::string>(),
				.magFilter = textureJson.at("magFilter").get<std::string>(),
				.wrapS = textureJson.at("wrapS").get<std::string>(),
				.wrapT = textureJson.at("wrapT").get<std::string>(),
				.generateMipmaps = textureJson.at("generateMipmaps").get<bool>()
			};

			m_textureRecords[id] = record;
		}
	}

	void JsonAssetDatabase::loadShaderRecords()
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
				.id = id,
				.vertexPath = shaderJson.at("vertexPath").get<std::string>(),
				.fragmentPath = shaderJson.at("fragmentPath").get<std::string>(),
			};

			m_shaderRecords[id] = record;
		}
	}

	void JsonAssetDatabase::loadMaterialRecords()
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
				.id = id,
				.shaderId = materialJson.at("shader").get<std::string>(),
				.blendMode = materialJson.at("blendMode").get<std::string>(),
				.tint = core::Color
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

	void JsonAssetDatabase::loadSpriteRecords()
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
				.id = id,
				.textureId = spriteJson.at("texture").get<std::string>(),
				.minPixel = math::Vector2f
				{
					spriteJson.at("minPixel").at(0).get<float>(),
					spriteJson.at("minPixel").at(1).get<float>()
				},
				.maxPixel = math::Vector2f
				{
					spriteJson.at("maxPixel").at(0).get<float>(),
					spriteJson.at("maxPixel").at(1).get<float>()
				}
			};

			m_spriteRecords[id] = record;
		}
	}
}
