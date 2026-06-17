#pragma once

#include "Assets/AssetLoader.hpp"
#include "Assets/Image.hpp"
#include "Assets/ShaderSource.hpp"

#include <string>
#include <filesystem>
#include <unordered_map>

namespace Cocoa::Assets
{
	// ToDo: Add Unit tests
	class AssetManager
	{
	public:
		AssetManager(const std::filesystem::path& rootPath);

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;

		const Image& LoadImage(const std::string& path);
		const ShaderSource& LoadShader(
			const std::string& shaderId,
			const std::string& vertexPath, 
			const std::string& fragmentPath
		);

	private:
		AssetLoader m_assetLoader;
		std::filesystem::path m_rootPath;
		std::unordered_map<std::string, Image> m_images;
		std::unordered_map<std::string, ShaderSource> m_shaderSources;
	};
}