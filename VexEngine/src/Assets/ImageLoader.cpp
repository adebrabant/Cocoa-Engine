#include "Assets/ImageLoader.hpp"

#include <string>
#include <filesystem>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace VexEngine::Assets
{
	Image ImageLoader::Load(const std::filesystem::path& path)
	{
		Image image;
		int width = 0;
		int height = 0;
		int channels = 0;
		unsigned char* data = stbi_load(
			path.string().c_str(),
			&width,
			&height,
			&channels,
			4
		);

		if (!data)
		{
			return image;
		}

		image.Width = width;
		image.Height = height;
		image.Channels = 4;

		const size_t size = static_cast<size_t>(width) * height * 4;

		image.Pixels.resize(size);
		std::memcpy(image.Pixels.data(), data, size);

		stbi_image_free(data);

		return image;
	}
}