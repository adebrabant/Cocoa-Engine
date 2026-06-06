#include "Assets/AssetManager.hpp"
#include "Assets/PathProvider.hpp"
#include "Assets/ImageLoader.hpp"
#include "Assets/Asset.hpp"

#include <string>
#include <filesystem>
#include <utility>
#include <stdexcept>
#include <cstdint>

namespace Cocoa::Assets
{
	AssetManager::AssetManager(PathProvider& pathProvider) :
		m_pathProvider(pathProvider),
		m_imageLoader(),
		m_rootPath(m_pathProvider.GetAssetsPath()),
		m_nextId{ 1 },
		m_texturePathCache(),
		m_texturePaths()
	{

	}

	Asset AssetManager::LoadTexture(const std::string& path)
	{
		if (auto it = m_texturePathCache.find(path); it != m_texturePathCache.end())
			return it->second;

		auto fullPath = m_rootPath / path;

		uint32_t idValue = m_nextId++;
		Asset asset(idValue, AssetType::Texture);

		m_texturePathCache.emplace(path, asset);
		m_texturePaths.emplace(idValue, fullPath);

		return asset;
	}

	Image AssetManager::LoadImage(const std::string& path)
	{
		auto fullPath = m_rootPath / path;

		return m_imageLoader.Load(fullPath);
	}
}