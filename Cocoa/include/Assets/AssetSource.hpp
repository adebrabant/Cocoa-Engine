#pragma once

#include <filesystem>
#include <vector>
#include <cstddef>

namespace Cocoa::Assets
{
	class AssetSource
	{
	public:
		virtual ~AssetSource() = default;
		[[nodiscard]] virtual std::vector<std::byte> ReadBytes(const std::filesystem::path& path) const = 0;
		[[nodiscard]] virtual bool Exists(const std::filesystem::path& path) const = 0;
	};
}