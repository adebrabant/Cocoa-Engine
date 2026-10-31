#include "assets/ResourceLoader.hpp"
#include "assets/AssetDatabase.hpp"
#include "assets/AssetManager.hpp"
#include "assets/AssetSource.hpp"
#include "assets/Image.hpp"
#include "graphics/GraphicsHandles.hpp"
#include "graphics/MaterialManager.hpp"
#include "graphics/ShaderManager.hpp"
#include "graphics/SpriteManager.hpp"
#include "graphics/Texture2D.hpp"
#include "graphics/TextureManager.hpp"
#include "graphics/TextureSpec.hpp"

#include <cstdint>
#include <vector>

namespace cocoa::assets
{
	ResourceLoader::ResourceLoader(
		AssetDatabase& assetDatabase,
		AssetSource& assetSource,
		AssetManager& assetManager,
		graphics::TextureManager& textureManager,
		graphics::ShaderManager& shaderManager,
		graphics::MaterialManager& materialManager,
		graphics::SpriteManager& spriteManager
	) :
		m_assetDatabase(assetDatabase),
		m_assetSource(assetSource),
		m_assetManager(assetManager),
		m_textureManager(textureManager),
		m_shaderManager(shaderManager),
		m_materialManager(materialManager),
		m_spriteManager(spriteManager)
	{

	}

	graphics::TextureHandle ResourceLoader::loadTexture(const std::string& textureId) const
	{
		const TextureRecord& record = m_assetDatabase.getTextureInfo(textureId);

		if (graphics::TextureHandle handle; m_textureManager.tryGetHandle(record.id, handle))
			return handle;

		const Image& image = m_assetManager.loadImage(
			record.path,
			m_assetSource.readBytes(record.path)
		);
		const graphics::TextureSpec spec
		{
			.id = record.id,
			.width = static_cast<uint32_t>(image.width),
			.height = static_cast<uint32_t>(image.height),
			.textureFormat = graphics::TextureSpec::parseFormat(record.format, image.channels),
			.minFilter = graphics::TextureSpec::parseFilter(record.minFilter),
			.magFilter = graphics::TextureSpec::parseFilter(record.magFilter),
			.wrapS = graphics::TextureSpec::parseWrap(record.wrapS),
			.wrapT = graphics::TextureSpec::parseWrap(record.wrapT),
			.generateMipmaps = record.generateMipmaps
		};

		return m_textureManager.load(spec, image.pixels.data());
	}

	graphics::ShaderHandle ResourceLoader::loadShader(const std::string& shaderId) const
	{
		const ShaderRecord& record = m_assetDatabase.getShaderInfo(shaderId);

		if (graphics::ShaderHandle handle; m_shaderManager.tryGetHandle(record.id, handle))
			return handle;

		const ShaderSource& source = m_assetManager.loadShader(
			record.id,
			m_assetSource.readBytes(record.vertexPath),
			m_assetSource.readBytes(record.fragmentPath)
		);

		return m_shaderManager.load(
			record.id,
			source.vertex,
			source.fragment
		);
	}

	graphics::MaterialHandle ResourceLoader::loadMaterial(const std::string& materialId) const
	{
		const MaterialRecord& record = m_assetDatabase.getMaterialInfo(materialId);
		const graphics::ShaderHandle shaderHandle = loadShader(record.shaderId);

		return m_materialManager.load(
			materialId,
			shaderHandle,
			record.blendMode,
			record.tint
		);
	}

	graphics::SpriteHandle ResourceLoader::loadSprite(const std::string& spriteId) const
	{
		const SpriteRecord& record = m_assetDatabase.getSpriteInfo(spriteId);
		const graphics::TextureHandle textureHandle = loadTexture(record.textureId);
		const graphics::Texture2D& texture2D = m_textureManager.get(textureHandle);
		const math::Vector2f textureSize(
			static_cast<float>(texture2D.getWidth()),
			static_cast<float>(texture2D.getHeight())
		);

		return m_spriteManager.load(
			record.id,
			textureHandle,
			record.minPixel,
			record.maxPixel,
			textureSize
		);
	}
}
