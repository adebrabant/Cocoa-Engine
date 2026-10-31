#pragma once

#include <cstdint>
#include <vector>
#include <filesystem>

namespace cocoa::assets
{
	struct Image;

	class AssetLoader
	{
	public:
		AssetLoader();
		~AssetLoader() = default;
		[[nodiscard]] Image loadImage(const std::filesystem::path& path) const;
		[[nodiscard]] Image loadImage(const std::vector<std::byte>& bytes) const;
		[[nodiscard]] std::string loadText(const std::filesystem::path& path) const;
		[[nodiscard]] std::string loadText(const std::vector<std::byte>& bytes) const;
	};
}
