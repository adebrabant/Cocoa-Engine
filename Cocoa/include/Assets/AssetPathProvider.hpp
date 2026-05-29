#pragma once

#include "Assets/IPathProvider.hpp"
#include <string>
#include <filesystem>

namespace Cocoa::Assets
{
	class AssetPathProvider : public IPathProvider
	{
	public:
		AssetPathProvider() = default;
		std::filesystem::path GetAssetsPath() const override;

	private:
		const std::string& m_assetPathName{ "Assets" };
	};
}