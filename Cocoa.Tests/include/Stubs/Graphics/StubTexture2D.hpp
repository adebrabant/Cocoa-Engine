#pragma once

#include <Graphics/Texture2D.hpp>

namespace Cocoa::Stubs
{
	class StubTexture2D : public Graphics::Texture2D
	{
	public:
		StubTexture2D() = default;
		~StubTexture2D() override = default;
		void Bind(uint32_t slot) const override;
		[[nodiscard]] uint32_t GetWidth() const override;
		[[nodiscard]] uint32_t GetHeight() const override;
	};
}