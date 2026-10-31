#pragma once

#include <string>
#include <filesystem>

namespace cocoa::assets
{
	class AssetPathProvider
	{
	public:
		AssetPathProvider();
		[[nodiscard]] const std::filesystem::path& getAssetsPath() const { return m_assetPath; }
		[[nodiscard]] const std::filesystem::path& getMetaDataPath() const { return m_metadataPath; };

	private:
		std::filesystem::path findPath(const std::string& path);

	private:
		std::filesystem::path m_assetPath;
		std::filesystem::path m_metadataPath;
	};
}
