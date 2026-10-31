#pragma once

#include <graphics/Texture2D.hpp>

namespace cocoa_benchmarks
{
	class StubTexture2D : public cocoa::graphics::Texture2D
	{
	public:
		StubTexture2D(cocoa::graphics::TextureSpec textureSpec, const unsigned char* pixels) { }
		~StubTexture2D() override = default;
		void Bind(uint32_t slot) const override { }
		[[nodiscard]] uint32_t GetWidth() const override { return 32; }
		[[nodiscard]] uint32_t GetHeight() const override { return 32; }
	};
}
