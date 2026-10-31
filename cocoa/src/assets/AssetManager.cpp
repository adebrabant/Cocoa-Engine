#include "assets/AssetManager.hpp"
#include "assets/AssetLoader.hpp"

namespace cocoa::assets
{
	AssetManager::AssetManager() :
		m_assetLoader(),
		m_images(),
		m_shaderSources()
	{

	}

	const Image& AssetManager::loadImage(
		const std::string& assetId,
		const std::vector<std::byte>& assetBytes)
	{
		if (auto it = m_images.find(assetId); it != m_images.end())
		{
			return it->second;
		}

		Image image = m_assetLoader.loadImage(assetBytes);

		auto [it, inserted] = m_images.emplace(assetId, std::move(image));

		return it->second;
	}

	const ShaderSource& AssetManager::loadShader(
		const std::string& shaderId,
		const std::vector<std::byte>& vertexBytes,
		const std::vector<std::byte>& fragmentBytes)
	{
		if (auto it = m_shaderSources.find(shaderId); it != m_shaderSources.end())
		{
			return it->second;
		}

		ShaderSource shaderSource
		{
			.vertex = m_assetLoader.loadText(vertexBytes),
			.fragment = m_assetLoader.loadText(fragmentBytes)
		};

		auto [it, inserted] = m_shaderSources.emplace(shaderId, std::move(shaderSource));

		return it->second;
	}
}
