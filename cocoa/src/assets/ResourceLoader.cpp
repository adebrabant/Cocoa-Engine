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

	graphics::TextureHandle ResourceLoader::LoadTexture(const std::string& textureId) const
	{
		const TextureRecord& record = m_assetDatabase.GetTextureInfo(textureId);

		if (graphics::TextureHandle handle; m_textureManager.TryGetHandle(record.id, handle))
			return handle;

		const Image& image = m_assetManager.LoadImage(
			record.path,
			m_assetSource.ReadBytes(record.path)
		);
		const graphics::TextureSpec spec
		{
			.Id = record.id,
			.Width = static_cast<uint32_t>(image.Width),
			.Height = static_cast<uint32_t>(image.Height),
			.Format = graphics::TextureSpec::ParseFormat(record.Format, image.Channels),
			.MinFilter = graphics::TextureSpec::ParseFilter(record.MinFilter),
			.MagFilter = graphics::TextureSpec::ParseFilter(record.MagFilter),
			.WrapS = graphics::TextureSpec::ParseWrap(record.WrapS),
			.WrapT = graphics::TextureSpec::ParseWrap(record.WrapT),
			.GenerateMipmaps = record.GenerateMipmaps
		};

		return m_textureManager.Load(spec, image.Pixels.data());
	}

	graphics::ShaderHandle ResourceLoader::LoadShader(const std::string& shaderId) const
	{
		const ShaderRecord& record = m_assetDatabase.GetShaderInfo(shaderId);

		if (graphics::ShaderHandle handle; m_shaderManager.TryGetHandle(record.Id, handle))
			return handle;

		const ShaderSource& source = m_assetManager.LoadShader(
			record.Id,
			m_assetSource.ReadBytes(record.VertexPath),
			m_assetSource.ReadBytes(record.FragmentPath)
		);

		return m_shaderManager.Load(
			record.Id,
			source.Vertex,
			source.Fragment
		);
	}

	graphics::MaterialHandle ResourceLoader::LoadMaterial(const std::string& materialId) const
	{
		const MaterialRecord& record = m_assetDatabase.GetMaterialInfo(materialId);
		const graphics::ShaderHandle shaderHandle = LoadShader(record.ShaderId);

		return m_materialManager.Load(
			materialId,
			shaderHandle,
			record.BlendMode,
			record.Tint
		);
	}

	graphics::SpriteHandle ResourceLoader::LoadSprite(const std::string& spriteId) const
	{
		const SpriteRecord& record = m_assetDatabase.GetSpriteInfo(spriteId);
		const graphics::TextureHandle textureHandle = LoadTexture(record.TextureId);
		const graphics::Texture2D& texture2D = m_textureManager.Get(textureHandle);
		const math::Vector2f textureSize(
			static_cast<float>(texture2D.GetWidth()),
			static_cast<float>(texture2D.GetHeight())
		);

		return m_spriteManager.Load(
			record.Id,
			textureHandle,
			record.MinPixel,
			record.MaxPixel,
			textureSize
		);
	}
}
