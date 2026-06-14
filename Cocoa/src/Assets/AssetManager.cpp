#include "Assets/AssetManager.hpp"
#include "Assets/AssetLoader.hpp"

#include <string>
#include <filesystem>

namespace Cocoa::Assets
{
	AssetManager::AssetManager(const std::filesystem::path& rootPath) :
		m_assetLoader(),
		m_rootPath(rootPath),
		m_images()
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
}