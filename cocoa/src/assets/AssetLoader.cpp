#include "assets/AssetLoader.hpp"
#include "assets/Image.hpp"

#include <fstream>
#include <sstream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <cstring>
#include <stb_image.h>

namespace cocoa::assets
{
	AssetLoader::AssetLoader()
	{
		stbi_set_flip_vertically_on_load(true);
	}

	Image AssetLoader::loadImage(const std::filesystem::path& path) const
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

		image.width = width;
		image.height = height;
		image.channels = 4;

		const size_t size = static_cast<size_t>(width) * height * 4;

		image.pixels.resize(size);
		std::memcpy(image.pixels.data(), data, size);

		stbi_image_free(data);

		return image;
	}

	Image AssetLoader::loadImage(const std::vector<std::byte>& bytes) const
	{
		Image image;
		int width = 0;
		int height = 0;
		int channels = 0;

		unsigned char* data = stbi_load_from_memory(
			reinterpret_cast<const unsigned char*>(bytes.data()),
			static_cast<int>(bytes.size()),
			&width,
			&height,
			&channels,
			4
		);

		if (!data)
		{
			return image;
		}

		image.width = width;
		image.height = height;
		image.channels = 4;

		const size_t size = static_cast<size_t>(width) * height * 4;

		image.pixels.resize(size);
		std::memcpy(image.pixels.data(), data, size);

		stbi_image_free(data);

		return image;
	}

	std::string AssetLoader::loadText(const std::filesystem::path& path) const
	{
		std::ifstream file(path, std::ios::in | std::ios::binary);

		if (!file)
		{
			throw std::runtime_error("Failed to open text file: " +
				path.string()
			);
		}

		std::ostringstream contents;
		contents << file.rdbuf();

		return contents.str();
	}

	std::string AssetLoader::loadText(const std::vector<std::byte>& bytes) const
	{
		if (bytes.empty())
			return std::string();

		return std::string(
			reinterpret_cast<const char*>(bytes.data()),
			bytes.size()
		);
	}
}
