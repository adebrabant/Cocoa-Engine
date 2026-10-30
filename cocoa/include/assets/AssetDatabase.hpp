#pragma once

#include "core/Color.hpp"
#include "math/Vector2f.hpp"

#include <string>

namespace cocoa::Assets
{
	struct TextureRecord
	{
		std::string id;
		std::string path;
		std::string Format;
		std::string MinFilter;
		std::string MagFilter;
		std::string WrapS;
		std::string WrapT;
		bool GenerateMipmaps;
	};

	struct ShaderRecord
	{
		std::string Id;
		std::string VertexPath;
		std::string FragmentPath;
	};

	struct MaterialRecord
	{
		std::string Id;
		std::string ShaderId;
		std::string BlendMode;
		Core::Color Tint;
	};

	struct SpriteRecord
	{
		std::string Id;
		std::string TextureId;
		Math::Vector2f MinPixel;
		Math::Vector2f MaxPixel;
	};

	class AssetDatabase
	{
	public:
		virtual ~AssetDatabase() = default;
		[[nodiscard]] virtual const TextureRecord& GetTextureInfo(const std::string& id) const = 0;
		[[nodiscard]] virtual const ShaderRecord& GetShaderInfo(const std::string& id) const = 0;
		[[nodiscard]] virtual const MaterialRecord& GetMaterialInfo(const std::string& id) const = 0;
		[[nodiscard]] virtual const SpriteRecord& GetSpriteInfo(const std::string& id) const = 0;
	};
}
