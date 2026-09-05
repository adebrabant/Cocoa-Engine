#pragma once

#include "Graphics/GraphicsHandles.hpp"

#include <string>

namespace Cocoa::Graphics
{
	class TextureManager;
	class ShaderManager;
	class MaterialManager;
	class SpriteManager;
}

namespace Cocoa::Assets
{
	class AssetDatabase;
	class AssetSource;
	class AssetManager;

	class ResourceLoader
	{
	public:
		ResourceLoader(
			AssetDatabase& assetDatabase,
			AssetSource& assetSource,
			AssetManager& assetManager,
			Graphics::TextureManager& textureManager,
			Graphics::ShaderManager& shaderManager,
			Graphics::MaterialManager& materialManager,
			Graphics::SpriteManager& spriteManager
		);

		~ResourceLoader() = default;

		ResourceLoader(const ResourceLoader&) = delete;
		ResourceLoader& operator=(const ResourceLoader&) = delete;

		ResourceLoader(ResourceLoader&&) = delete;
		ResourceLoader& operator=(ResourceLoader&&) = delete;

		[[nodiscard]] Graphics::TextureHandle LoadTexture(const std::string& textureId) const;
		[[nodiscard]] Graphics::ShaderHandle LoadShader(const std::string& shaderId) const;
		[[nodiscard]] Graphics::MaterialHandle LoadMaterial(const std::string& materialId) const;
		[[nodiscard]] Graphics::SpriteHandle LoadSprite(const std::string& spriteId) const;

	private:
		AssetDatabase& m_assetDatabase;
		AssetSource& m_assetSource;
		AssetManager& m_assetManager;
		Graphics::TextureManager& m_textureManager;
		Graphics::ShaderManager& m_shaderManager;
		Graphics::MaterialManager& m_materialManager;
		Graphics::SpriteManager& m_spriteManager;
	};
}