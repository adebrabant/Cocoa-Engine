#pragma once

#include <cstdint>
#include <string>

namespace Cocoa::Graphics
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
		std::string Id{ "" };

		uint32_t Width{ 0 };
		uint32_t Height{ 0 };

		TextureFormat Format{ TextureFormat::RGBA8 };

		TextureFilter MinFilter{ TextureFilter::Linear };
		TextureFilter MagFilter{ TextureFilter::Linear };

		TextureWrap WrapS{ TextureWrap::ClampToEdge };
		TextureWrap WrapT{ TextureWrap::ClampToEdge };

		bool GenerateMipmaps{ false };

		static TextureFormat ParseFormat(std::string_view value, uint32_t channels);
		static TextureFilter ParseFilter(std::string_view value);
		static TextureWrap ParseWrap(std::string_view value);
	};
}