#pragma once

#include "Graphics/GraphicsHandles.hpp"

#include <string>

namespace Cocoa::Graphics
{
	class TextureManager;
	class ShaderManager;
	class MaterialManager;
}

namespace Cocoa::Assets
{
	class AssetDatabase;
	class AssetManager;

	class ResourceLoader
	{
	public:
		ResourceLoader(
			AssetDatabase& assetDatabase,
			AssetManager& assetManager,
			Graphics::TextureManager& textureManager,
			Graphics::ShaderManager& shaderManager,
			Graphics::MaterialManager& materialManager
		);

		~ResourceLoader() = default;

		Graphics::TextureHandle LoadTexture(const std::string& textureId);
		Graphics::ShaderHandle LoadShader(const std::string& shaderId);


	private:
		AssetDatabase& m_assetDatabase;
		AssetManager& m_assetManager;
		Graphics::TextureManager& m_textureManager;
		Graphics::ShaderManager& m_shaderManager;
		Graphics::MaterialManager& m_materialManager;
	};
}