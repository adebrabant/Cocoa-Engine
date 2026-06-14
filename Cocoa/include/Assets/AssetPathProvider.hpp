#pragma once

#include <string>
#include <filesystem>

namespace Cocoa::Assets
{
	class AssetPathProvider
	{
	public:
		AssetPathProvider();
		const std::filesystem::path& GetAssetsPath() const { return m_assetPath; }
		const std::filesystem::path& GetMetaDataPath() const { return m_metadataPath; };

	private:
		std::filesystem::path FindPath(const std::string& path);

	private:
		std::filesystem::path m_assetPath;
		std::filesystem::path m_metadataPath;
	};
}