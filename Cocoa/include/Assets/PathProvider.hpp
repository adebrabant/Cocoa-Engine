#pragma once

#include <filesystem>

namespace Cocoa::Assets
{
	class PathProvider
	{
	public:
		virtual ~PathProvider() = default;
		virtual std::filesystem::path GetAssetsPath() const = 0;
	};
}