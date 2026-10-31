#pragma once

#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <cstddef>
#include <stdexcept>

namespace cocoa_tests::Helpers
{
	inline static std::vector<std::byte> ReadFileBytes(const std::filesystem::path& path)
	{
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		if (!file)
		{
			throw std::runtime_error(
				"Failed to open test asset: " + path.string()
			);
		}
		const std::streamsize size = file.tellg();

		if (size == 0)
			return {};

		file.seekg(0, std::ios::beg);
		std::vector<std::byte> bytes(static_cast<size_t>(size));

		if (!file.read(reinterpret_cast<char*>(bytes.data()), size))
		{
			throw std::runtime_error(
				"Failed to read test asset file: " + path.string()
			);
		}

		return bytes;
	}
}