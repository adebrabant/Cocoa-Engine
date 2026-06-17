#pragma once

#include <Graphics/Texture2D.hpp>

namespace Cocoa::Stubs
{
	class StubTexture2D : public Graphics::Texture2D
	{
	public:
		StubTexture2D() = default;
		~StubTexture2D() = default;
		void Bind(uint32_t slot) const override;
		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
	};
}