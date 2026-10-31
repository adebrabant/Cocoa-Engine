#pragma once

#include "core/Color.hpp"
#include "math/Vector2f.hpp"

#include <string>

namespace cocoa::assets
{
	struct TextureRecord
	{
		std::string id;
		std::string path;
		std::string format;
		std::string minFilter;
		std::string magFilter;
		std::string wrapS;
		std::string wrapT;
		bool generateMipmaps;
	};

	struct ShaderRecord
	{
		std::string id;
		std::string vertexPath;
		std::string fragmentPath;
	};

	struct MaterialRecord
	{
		std::string id;
		std::string shaderId;
		std::string blendMode;
		core::Color tint;
	};

	struct SpriteRecord
	{
		std::string id;
		std::string textureId;
		math::Vector2f minPixel;
		math::Vector2f maxPixel;
	};

	class AssetDatabase
	{
	public:
		virtual ~AssetDatabase() = default;
		[[nodiscard]] virtual const TextureRecord& getTextureInfo(const std::string& id) const = 0;
		[[nodiscard]] virtual const ShaderRecord& getShaderInfo(const std::string& id) const = 0;
		[[nodiscard]] virtual const MaterialRecord& getMaterialInfo(const std::string& id) const = 0;
		[[nodiscard]] virtual const SpriteRecord& getSpriteInfo(const std::string& id) const = 0;
	};
}
