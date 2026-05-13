#pragma once

#include <filesystem>

namespace VexEngine::Assets
{
	class IPathProvider
	{
	public:
		virtual ~IPathProvider() = default;
		virtual std::filesystem::path GetAssetsPath() const = 0;
	};
}