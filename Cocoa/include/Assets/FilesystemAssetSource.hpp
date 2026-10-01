#pragma once

#include "Assets/AssetSource.hpp"

namespace Cocoa::Assets
{
	class FilesystemAssetSource : public AssetSource
	{
	public:
		explicit FilesystemAssetSource(std::filesystem::path rootpath);
		std::vector<std::byte> ReadBytes(const std::filesystem::path& path) const override;
		bool Exists(const std::filesystem::path& path) const override;

	private:
		[[nodiscard]] std::filesystem::path Resolve(const std::filesystem::path& path) const;

	private:
		std::filesystem::path m_rootPath;
	};
}