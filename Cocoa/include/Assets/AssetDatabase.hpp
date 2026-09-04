#pragma once

#include "Core/Color.hpp"
#include "Math/Vector2f.hpp"

#include <string>

namespace Cocoa::Assets
{
	struct TextureRecord
	{
		std::string Id;
		std::string Path;
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
		std::string TextureId;
		Core::Color Tint;
	};

	struct SpriteRecord
	{
		std::string Id;
		std::string TextureId;
		Math::Vector2f MinUV;
		Math::Vector2f MaxUV;
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