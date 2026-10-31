#pragma once

#include <graphics/Texture2D.hpp>

namespace cocoa_tests::stubs
{
	class StubTexture2D : public cocoa::graphics::Texture2D
	{
	public:
		StubTexture2D() = default;
		~StubTexture2D() override = default;
		void Bind(uint32_t slot) const override;
		[[nodiscard]] uint32_t GetWidth() const override;
		[[nodiscard]] uint32_t GetHeight() const override;
	};
}
