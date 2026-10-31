#pragma once

#include <graphics/Texture2D.hpp>

namespace cocoa_tests::stubs
{
	class StubTexture2D : public cocoa::graphics::Texture2D
	{
	public:
		StubTexture2D() = default;
		~StubTexture2D() override = default;
		void bind(uint32_t slot) const override;
		[[nodiscard]] uint32_t getWidth() const override;
		[[nodiscard]] uint32_t getHeight() const override;
	};
}
