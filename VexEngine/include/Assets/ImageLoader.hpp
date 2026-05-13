#pragma once

#include <vector>
#include <cstdint>
#include <filesystem>

namespace VexEngine::Assets
{
	struct Image
	{
		std::vector<uint8_t> Pixels;
		int Width{ 0 };
		int Height{ 0 };
		int Channels{ 4 };
	};

	class ImageLoader
	{
	public:
		ImageLoader() = default;
		~ImageLoader() = default;
		Image Load(const std::filesystem::path& path);
	};
}