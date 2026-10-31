#pragma once

#include "graphics/GraphicsHandles.hpp"

#include <string>

namespace cocoa::graphics
{
	class TextureManager;
	class ShaderManager;
	class MaterialManager;
	class SpriteManager;
}

namespace cocoa::assets
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
			graphics::TextureManager& textureManager,
			graphics::ShaderManager& shaderManager,
			graphics::MaterialManager& materialManager,
			graphics::SpriteManager& spriteManager
		);

		~ResourceLoader() = default;

		ResourceLoader(const ResourceLoader&) = delete;
		ResourceLoader& operator=(const ResourceLoader&) = delete;

		ResourceLoader(ResourceLoader&&) = delete;
		ResourceLoader& operator=(ResourceLoader&&) = delete;

		[[nodiscard]] graphics::TextureHandle LoadTexture(const std::string& textureId) const;
		[[nodiscard]] graphics::ShaderHandle LoadShader(const std::string& shaderId) const;
		[[nodiscard]] graphics::MaterialHandle LoadMaterial(const std::string& materialId) const;
		[[nodiscard]] graphics::SpriteHandle LoadSprite(const std::string& spriteId) const;

	private:
		AssetDatabase& m_assetDatabase;
		AssetSource& m_assetSource;
		AssetManager& m_assetManager;
		graphics::TextureManager& m_textureManager;
		graphics::ShaderManager& m_shaderManager;
		graphics::MaterialManager& m_materialManager;
		graphics::SpriteManager& m_spriteManager;
	};
}
