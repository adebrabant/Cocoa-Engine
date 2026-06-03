#pragma once

#include "Assets/IPathProvider.hpp"
#include "Assets/ImageLoader.hpp"
#include "Assets/Asset.hpp"

#include <string>
#include <unordered_map>
#include <cstdint>

namespace Cocoa::Assets
{
	class AssetManager
	{
	public:
		AssetManager(IPathProvider& pathProvider);
		Asset LoadTexture(const std::string& path);
		Image LoadImage(const std::string& path);

	private:
		IPathProvider& m_pathProvider;
		ImageLoader m_imageLoader;
		uint32_t m_nextId{ 1 };
		std::unordered_map<std::string, Asset> m_texturePathCache;
		std::unordered_map<uint32_t, std::filesystem::path> m_texturePaths;
	};
}