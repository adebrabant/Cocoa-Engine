#pragma once

#include <filesystem>
#include <vector>
#include <cstddef>

namespace cocoa::assets
{
	class AssetSource
	{
	public:
		virtual ~AssetSource() = default;
		[[nodiscard]] virtual std::vector<std::byte> readBytes(const std::filesystem::path& path) const = 0;
		[[nodiscard]] virtual bool exists(const std::filesystem::path& path) const = 0;
	};
}
