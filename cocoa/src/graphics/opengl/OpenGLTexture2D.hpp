#pragma once

#include "graphics/Texture2D.hpp"
#include "graphics/TextureSpec.hpp"

#include <cstdint>

namespace cocoa::graphics
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(TextureSpec textureSpec, const unsigned char* pixels);
		~OpenGLTexture2D() override;

		OpenGLTexture2D(const OpenGLTexture2D&) = delete;
		OpenGLTexture2D& operator = (const OpenGLTexture2D&) = delete;

		OpenGLTexture2D(OpenGLTexture2D&& other) noexcept;
		OpenGLTexture2D& operator=(OpenGLTexture2D&& other) noexcept;

		void bind(uint32_t slot) const override;
		[[nodiscard]] uint32_t getWidth() const override;
		[[nodiscard]] uint32_t getHeight() const override;

	private:
		void Destroy();

	private:
		uint32_t m_textureId{ 0 };
		TextureSpec m_textureSpec;
	};
}
