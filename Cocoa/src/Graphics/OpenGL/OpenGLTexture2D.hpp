#pragma once

#include "Graphics/TextureSpec.hpp"

#include <cstdint>

namespace Cocoa::Graphics
{
	class OpenGLTexture2D 
	{
	public:
		OpenGLTexture2D(TextureSpec textureSpec, const unsigned char* pixels);
		~OpenGLTexture2D();

		OpenGLTexture2D(const OpenGLTexture2D&) = delete;
		OpenGLTexture2D& operator = (const OpenGLTexture2D&) = delete;

		OpenGLTexture2D(OpenGLTexture2D&& other) noexcept;
		OpenGLTexture2D& operator=(OpenGLTexture2D&& other) noexcept;

		void Bind(uint32_t slot = 0) const;
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

	private:
		void Destroy();

	private:
		uint32_t m_textureId{ 0 };
		TextureSpec m_textureSpec;
	};
}