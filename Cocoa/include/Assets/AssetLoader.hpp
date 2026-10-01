#pragma once

#include <cstdint>
#include <vector>
#include <filesystem>

namespace Cocoa::Assets
{
	struct Image;

	class AssetLoader
	{
	public:
		AssetLoader();
		~AssetLoader() = default;
		[[nodiscard]] Image LoadImage(const std::filesystem::path& path) const;
		[[nodiscard]] Image LoadImage(const std::vector<std::byte>& bytes) const;
		[[nodiscard]] std::string LoadText(const std::filesystem::path& path) const;
		[[nodiscard]] std::string LoadText(const std::vector<std::byte>& bytes) const;
	};
}