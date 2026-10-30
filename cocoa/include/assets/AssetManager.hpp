#pragma once

#include "assets/AssetLoader.hpp"
#include "assets/Image.hpp"
#include "assets/ShaderSource.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace cocoa::Assets
{
	class AssetManager
	{
	public:
		AssetManager();

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;

		const Image& LoadImage(
			const std::string& assetId, 
			const std::vector<std::byte>& assetBytes
		);

		const ShaderSource& LoadShader(
			const std::string& shaderId,
			const std::vector<std::byte>& vertexBytes,
			const std::vector<std::byte>& fragmentBytes
		);

	private:
		AssetLoader m_assetLoader;
		std::unordered_map<std::string, Image> m_images;
		std::unordered_map<std::string, ShaderSource> m_shaderSources;
	};
}