#include "Assets/ResourceLoader.hpp"
#include "Assets/AssetDatabase.hpp"
#include "Assets/AssetManager.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/GraphicsHandles.hpp"
#include "Graphics/TextureSpec.hpp"
#include "Assets/Image.hpp"

#include <string>
#include <cstdint>

namespace Cocoa::Assets
{
	ResourceLoader::ResourceLoader(
		AssetDatabase& assetDatabase, 
		AssetManager& assetManager, 
		Graphics::TextureManager& textureManager, 
		Graphics::ShaderManager& shaderManager, 
		Graphics::MaterialManager& materialManager
	) :
		m_assetDatabase(assetDatabase),
		m_assetManager(assetManager),
		m_textureManager(textureManager),
		m_shaderManager(shaderManager),
		m_materialManager(materialManager)
	{

	}

	Graphics::TextureHandle ResourceLoader::LoadTexture(const std::string& textureId) const
	{
		const TextureRecord& record = m_assetDatabase.GetTextureInfo(textureId);
		const Image& image = m_assetManager.LoadImage(record.Path);
		const Graphics::TextureSpec spec
		{
			.Id = record.Id,
			.Width = static_cast<uint32_t>(image.Width),
			.Height = static_cast<uint32_t>(image.Height),
			.Format = Graphics::TextureSpec::ParseFormat(record.Format, image.Channels),
			.MinFilter = Graphics::TextureSpec::ParseFilter(record.MinFilter),
			.MagFilter = Graphics::TextureSpec::ParseFilter(record.MagFilter),
			.WrapS = Graphics::TextureSpec::ParseWrap(record.WrapS),
			.WrapT = Graphics::TextureSpec::ParseWrap(record.WrapT),
			.GenerateMipmaps = record.GenerateMipmaps
		};

		return m_textureManager.Load(spec, image.Pixels.data());
	}

	Graphics::ShaderHandle ResourceLoader::LoadShader(const std::string& shaderId) const
	{
		const ShaderRecord& record = m_assetDatabase.GetShaderInfo(shaderId);
		const ShaderSource& source = m_assetManager.LoadShader(
			record.Id,
			record.VertexPath,
			record.FragmentPath
		);

		return m_shaderManager.Load(
			record.Id,
			source.Vertex,
			source.Fragment
		);
	}

	Graphics::MaterialHandle ResourceLoader::LoadMaterial(const std::string& materialId) const
	{
		const MaterialRecord& record = m_assetDatabase.GetMaterialInfo(materialId);
		const Graphics::ShaderHandle shaderHandle = LoadShader(record.ShaderId);
		const Graphics::TextureHandle textureHandle = LoadTexture(record.TextureId);
		
		return m_materialManager.Load(
			materialId,
			shaderHandle,
			textureHandle,
			record.Tint
		);
	}
}