#include "Graphics/OpenGL/OpenGLTexture2D.hpp"
#include "Graphics/TextureSpec.hpp"

#include <GL/glew.h>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <cassert>

namespace Cocoa::Graphics
{
	static GLenum ToWrap(TextureWrap wrap)
	{
		switch (wrap)
		{
		case Cocoa::Graphics::TextureWrap::Repeat:
			return GL_REPEAT;
		case Cocoa::Graphics::TextureWrap::ClampToEdge:
			return GL_CLAMP_TO_EDGE;
		default:
			throw std::runtime_error("Invalid texture wrap mode.");
		}
	}

	static GLenum ToFilter(TextureFilter filter)
	{
		switch (filter)
		{
		case Cocoa::Graphics::TextureFilter::Nearest:
			return GL_NEAREST;
		case Cocoa::Graphics::TextureFilter::Linear:
			return GL_LINEAR;
		case Cocoa::Graphics::TextureFilter::NearestMipmapNearest:
			return GL_NEAREST_MIPMAP_NEAREST;
		case Cocoa::Graphics::TextureFilter::LinearMipmapNearest:
			return GL_LINEAR_MIPMAP_NEAREST;
		case Cocoa::Graphics::TextureFilter::NearestMipmapLinear:
			return GL_NEAREST_MIPMAP_LINEAR;
		case Cocoa::Graphics::TextureFilter::LinearMipmapLinear:
			return GL_LINEAR_MIPMAP_LINEAR;
		default:
			throw std::runtime_error("Invalid texture filter.");
		}
	}

	static GLenum ToInternalFormat(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB8:
			return GL_RGB8;

		case TextureFormat::RGBA8:
			return GL_RGBA8;

		default:
			throw std::runtime_error("Invalid texture internal format.");
		}
	}

	static GLenum ToDataFormat(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB8:
			return GL_RGB;

		case TextureFormat::RGBA8:
			return GL_RGBA;

		default:
			throw std::runtime_error("Invalid texture data format.");
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(TextureSpec textureSpec, const unsigned char* pixels) :
		m_textureSpec(std::move(textureSpec)),
		m_textureId{ 0 }
	{
		if (!pixels)
			throw std::invalid_argument("Texture pixel data cannot be null.");

		GLuint texture{ 0 };
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ToWrap(m_textureSpec.WrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ToWrap(m_textureSpec.WrapT));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ToFilter(m_textureSpec.MinFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ToFilter(m_textureSpec.MagFilter));

		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			ToInternalFormat(m_textureSpec.Format),
			static_cast<GLsizei>(m_textureSpec.Width),
			static_cast<GLsizei>(m_textureSpec.Height),
			0, 
			ToDataFormat(m_textureSpec.Format),
			GL_UNSIGNED_BYTE, 
			pixels
		);

		if (m_textureSpec.GenerateMipmaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		m_textureId = static_cast<uint32_t>(texture);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		Destroy();
	}

	OpenGLTexture2D::OpenGLTexture2D(OpenGLTexture2D&& other) noexcept
	{
		m_textureId = other.m_textureId;
		m_textureSpec = other.m_textureSpec;
		other.m_textureId = 0;
	}

	OpenGLTexture2D& OpenGLTexture2D::operator=(OpenGLTexture2D&& other) noexcept
	{
		if (this == &other)
			return *this;

		if (m_textureId != 0)
		{
			Destroy();
		}

		m_textureId = other.m_textureId;
		m_textureSpec = other.m_textureSpec;
		other.m_textureId = 0;

		return *this;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		assert(m_textureId != 0);
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	uint32_t OpenGLTexture2D::GetWidth() const
	{
		return m_textureSpec.Width;
	}

	uint32_t OpenGLTexture2D::GetHeight() const
	{
		return m_textureSpec.Height;
	}

	void OpenGLTexture2D::Destroy()
	{
		if (m_textureId == 0)
			return;

		glDeleteTextures(1, &m_textureId);
		m_textureId = 0;
	}
}