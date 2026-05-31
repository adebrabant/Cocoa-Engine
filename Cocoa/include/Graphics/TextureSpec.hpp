#pragma once

#include <cstdint>

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
		uint32_t Width{ 0 };
		uint32_t Height{ 0 };

		TextureFormat Format{ TextureFormat::RGBA8 };

		TextureFilter MinFilter{ TextureFilter::Linear };
		TextureFilter MagFilter{ TextureFilter::Linear };

		TextureWrap WrapS{ TextureWrap::ClampToEdge };
		TextureWrap WrapT{ TextureWrap::ClampToEdge };

		bool GenerateMipmaps{ false };
	};
}