#pragma once

#include "Assets/PathProvider.hpp"
#include <string>
#include <filesystem>

namespace Cocoa::Assets
{
	class AssetPathProvider : public PathProvider
	{
	public:
		AssetPathProvider() = default;
		std::filesystem::path GetAssetsPath() const override;

	private:
		const std::string& m_assetPathName{ "Assets" };
	};
}