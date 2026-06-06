#pragma once

#include "Assets/PathProvider.hpp"
#include "Assets/ImageLoader.hpp"
#include "Assets/Asset.hpp"

#include <string>
#include <filesystem>
#include <unordered_map>
#include <cstdint>

namespace Cocoa::Assets
{
	class AssetManager
	{
	public:
		AssetManager(PathProvider& pathProvider);
		Asset LoadTexture(const std::string& path);
		Image LoadImage(const std::string& path);

	private:
		PathProvider& m_pathProvider;
		ImageLoader m_imageLoader;
		std::filesystem::path m_rootPath;
		uint32_t m_nextId{ 1 };
		std::unordered_map<std::string, Asset> m_texturePathCache;
		std::unordered_map<uint32_t, std::filesystem::path> m_texturePaths;
	};
}