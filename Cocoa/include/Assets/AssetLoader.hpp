#pragma once

#include <cstdint>
#include <filesystem>

namespace Cocoa::Assets
{
	struct Image;

	class AssetLoader
	{
	public:
		AssetLoader();
		~AssetLoader() = default;
		Image Load(const std::filesystem::path& path) const;
		std::string LoadTextFile(const std::filesystem::path& path) const;
	};
}