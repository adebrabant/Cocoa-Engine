#include "Assets/AssetManager.hpp"
#include "Assets/AssetLoader.hpp"

namespace Cocoa::Assets
{
	AssetManager::AssetManager() :
		m_assetLoader(),
		m_images(),
		m_shaderSources()
	{

	}

	const Image& AssetManager::LoadImage(
		const std::string& assetId,
		const std::vector<std::byte>& assetBytes)
	{
		if (auto it = m_images.find(assetId); it != m_images.end())
		{
			return it->second;
		}

		Image image = m_assetLoader.LoadImage(assetBytes);

		auto [it, inserted] = m_images.emplace(assetId, std::move(image));

		return it->second;
	}

	const ShaderSource& AssetManager::LoadShader(
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
			.Vertex = m_assetLoader.LoadText(vertexBytes),
			.Fragment = m_assetLoader.LoadText(fragmentBytes)
		}; 

		auto [it, inserted] = m_shaderSources.emplace(shaderId, std::move(shaderSource));

		return it->second;
	}
}