#include "Assets/AssetManager.hpp"
#include "Assets/AssetLoader.hpp"

#include <string>
#include <filesystem>

namespace Cocoa::Assets
{
	AssetManager::AssetManager(const std::filesystem::path& rootPath) :
		m_assetLoader(),
		m_rootPath(rootPath),
		m_images(),
		m_shaderSources()
	{

	}

	const Image& AssetManager::LoadImage(const std::string& path)
	{
		if (auto it = m_images.find(path); it != m_images.end())
		{
			return it->second;
		}

		auto fullPath = m_rootPath / path;

		Image image = m_assetLoader.Load(fullPath);

		auto [it, inserted] = m_images.emplace(path, std::move(image));

		return it->second;
	}

	const ShaderSource& AssetManager::LoadShader(
		const std::string& shaderId, 
		const std::string& vertexPath, 
		const std::string& fragmentPath)
	{
		if (auto it = m_shaderSources.find(shaderId); it != m_shaderSources.end())
		{
			return it->second;
		}

		ShaderSource shaderSource
		{
			.Vertex = m_assetLoader.LoadTextFile(m_rootPath / vertexPath),
			.Fragment = m_assetLoader.LoadTextFile(m_rootPath / fragmentPath)
		}; 

		auto [it, inserted] = m_shaderSources.emplace(shaderId, std::move(shaderSource));

		return it->second;
	}
}