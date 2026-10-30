#pragma once

#include <graphics/Texture2D.hpp>

namespace CocoaBenchmarks
{
	class StubTexture2D : public cocoa::Graphics::Texture2D
	{
	public:
		StubTexture2D(cocoa::Graphics::TextureSpec textureSpec, const unsigned char* pixels) { }
		~StubTexture2D() override = default;
		void Bind(uint32_t slot) const override { }
		[[nodiscard]] uint32_t GetWidth() const override { return 32; }
		[[nodiscard]] uint32_t GetHeight() const override { return 32; }
	};
}