#pragma once

#include "Core/Color.hpp"
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

	class AssetDatabase
	{
	public:
		virtual ~AssetDatabase() = default;
		virtual const TextureRecord& GetTextureInfo(const std::string& id) const = 0;
		virtual const ShaderRecord& GetShaderInfo(const std::string& id) const = 0;
		virtual const MaterialRecord& GetMaterialInfo(const std::string& id) const = 0;
	};
}