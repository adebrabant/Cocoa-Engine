#pragma once

#include "assets/AssetSource.hpp"

namespace cocoa::assets
{
	class FilesystemAssetSource : public AssetSource
	{
	public:
		explicit FilesystemAssetSource(std::filesystem::path rootpath);
		std::vector<std::byte> readBytes(const std::filesystem::path& path) const override;
		bool exists(const std::filesystem::path& path) const override;

	private:
		[[nodiscard]] std::filesystem::path resolve(const std::filesystem::path& path) const;

	private:
		std::filesystem::path m_rootPath;
	};
}
