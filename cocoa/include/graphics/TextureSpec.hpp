#pragma once

#include <cstdint>
#include <string>

namespace cocoa::graphics
{
	enum class TextureFormat
	{
		None = 0,
		RGB8,
		RGBA8
	};

	enum class TextureFilter
	{
		Nearest = 0,
		Linear,
		NearestMipmapNearest,
		LinearMipmapNearest,
		NearestMipmapLinear,
		LinearMipmapLinear
	};

	enum class TextureWrap
	{
		Repeat = 0,
		ClampToEdge
	};

	struct TextureSpec
	{
		std::string id{ "" };

		uint32_t width{ 0 };
		uint32_t height{ 0 };

		TextureFormat textureFormat{ TextureFormat::RGBA8 };

		TextureFilter minFilter{ TextureFilter::Linear };
		TextureFilter magFilter{ TextureFilter::Linear };

		TextureWrap wrapS{ TextureWrap::ClampToEdge };
		TextureWrap wrapT{ TextureWrap::ClampToEdge };

		bool generateMipmaps{ false };

		static TextureFormat parseFormat(std::string_view value, uint32_t channels);
		static TextureFilter parseFilter(std::string_view value);
		static TextureWrap parseWrap(std::string_view value);
	};
}
