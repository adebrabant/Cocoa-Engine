#include "Assets/AssetManager.hpp"
#include "Assets/IPathProvider.hpp"
#include "Assets/ImageLoader.hpp"
#include "Assets/Asset.hpp"

#include <string>
#include <filesystem>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace Cocoa::Assets
{
	AssetManager::AssetManager(IPathProvider& pathProvider) :
		m_pathProvider(pathProvider),
		m_imageLoader(),
		m_texturePathCache(),
		m_texturePaths()
	{

	}

	Asset AssetManager::LoadTexture(const std::string& path)
	{
		if (auto it = m_texturePathCache.find(path); it != m_texturePathCache.end())
			return it->second;

		auto basePath = m_pathProvider.GetAssetsPath();
		auto fullPath = basePath / path;

		uint32_t idValue = m_nextId++;
		Asset asset(idValue, AssetType::Texture);

		m_texturePathCache.emplace(path, asset);
		m_texturePaths.emplace(idValue, fullPath);

		return asset;
	}

	Image AssetManager::LoadImage(const std::string& path)
	{
		auto basePath = m_pathProvider.GetAssetsPath();
		auto fullPath = basePath / path;

		return m_imageLoader.Load(fullPath);
	}
}