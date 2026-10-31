#include "assets/FilesystemAssetSource.hpp"

#include <fstream>
#include <stdexcept>
#include <utility>

namespace cocoa::assets
{
	FilesystemAssetSource::FilesystemAssetSource(std::filesystem::path rootpath)
		: m_rootPath(std::move(rootpath))
	{

	}

	std::vector<std::byte> FilesystemAssetSource::readBytes(const std::filesystem::path& path) const
	{
		const std::filesystem::path fullpath = resolve(path);
		std::ifstream file(fullpath, std::ios::binary | std::ios::ate);
		if (!file)
		{
			throw std::runtime_error(
				"Failed to open asset: " + fullpath.string()
			);
		}

		const std::streamsize size = file.tellg();
		if (size < 0)
		{
			throw std::runtime_error(
				"Failed to get size for asset file: " + fullpath.string()
			);
		}

		file.seekg(0, std::ios::beg);
		std::vector<std::byte> bytes(static_cast<size_t>(size));

		if (!file.read(reinterpret_cast<char*>(bytes.data()), size))
		{
			throw std::runtime_error(
				"Failed to read asset file: " + fullpath.string()
			);
		}

		return bytes;
	}

	bool FilesystemAssetSource::exists(const std::filesystem::path& path) const
	{
		return std::filesystem::exists(resolve(path));
	}

	std::filesystem::path FilesystemAssetSource::resolve(const std::filesystem::path& path) const
	{
		if (path.is_absolute())
			return path;

		return m_rootPath / path;
	}
}
