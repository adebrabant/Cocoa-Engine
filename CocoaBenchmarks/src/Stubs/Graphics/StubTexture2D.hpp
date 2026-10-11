#pragma once

#include <Graphics/Texture2D.hpp>

namespace CocoaBenchmarks
{
	class StubTexture2D : public Cocoa::Graphics::Texture2D
	{
	public:
		StubTexture2D(Cocoa::Graphics::TextureSpec textureSpec, const unsigned char* pixels) { }
		~StubTexture2D() override = default;
		void Bind(uint32_t slot) const override { }
		[[nodiscard]] uint32_t GetWidth() const override { return 32; }
		[[nodiscard]] uint32_t GetHeight() const override { return 32; }
	};
}