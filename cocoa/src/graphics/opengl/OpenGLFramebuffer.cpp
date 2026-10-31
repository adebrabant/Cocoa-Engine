#include "graphics/opengl/OpenGLFramebuffer.hpp"

#include <GL/glew.h>
#include <iostream>

namespace cocoa::graphics
{
    static GLenum ToOpenGLColorFormat(const ColorFormat& format)
    {
        switch (format)
        {
            case ColorFormat::RGB8:
                return GL_RGB8;
            case ColorFormat::RGBA8:
                return GL_RGBA8;
            case ColorFormat::RGBA16F:
                return GL_RGBA16F;
            default:
                return GL_RGB8;
        }
    }

    static GLenum ToOpenGLColorDataFormat(const ColorFormat& format)
    {
        switch (format)
        {
            case ColorFormat::RGB8:
                return GL_RGB;
            case ColorFormat::RGBA8:
                return GL_RGBA;
            case ColorFormat::RGBA16F:
                return GL_RGBA;
            default:
                return GL_RGB;
        }
    }

    static GLenum ToOpenGLDepthStencilFormat(const DepthStencilFormat& format)
    {
        switch (format)
        {
            case DepthStencilFormat::Depth24:
                return GL_DEPTH_COMPONENT24;
            case DepthStencilFormat::Stencil8:
                return GL_STENCIL_INDEX8;
            case DepthStencilFormat::Depth24Stencil8:
                return GL_DEPTH24_STENCIL8;
            default:
                return GL_DEPTH;
        }
    }

    static GLenum ToOpenGLDepthStencilAttachment(const DepthStencilFormat& format)
    {
        switch (format)
        {
            case DepthStencilFormat::Depth24:
                return GL_DEPTH_ATTACHMENT;
            case DepthStencilFormat::Stencil8:
                return GL_STENCIL_ATTACHMENT;
            case DepthStencilFormat::Depth24Stencil8:
                return GL_DEPTH_STENCIL_ATTACHMENT;
            default:
                return GL_DEPTH_ATTACHMENT;
        }
    }

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& framebufferSpec) :
        m_framebufferSpec(framebufferSpec),
        m_fbo(0),
        m_rbo(0)
    {
        GLuint fbo{0};
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        // Create the textures and bind them to the fbo
        std::vector<GLenum> colorAttachmentIndexes;
        for (auto i = 0; i < m_framebufferSpec.colorFormats.size(); ++i)
        {
            auto colorFormat = m_framebufferSpec.colorFormats[i];
            GLuint textureColorbuffer;
            glGenTextures(1, &textureColorbuffer);
            glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                // Tell Open GL how to store the channels
                static_cast<GLint>(ToOpenGLColorFormat(colorFormat)),
                static_cast<GLsizei>(framebufferSpec.width),
                static_cast<GLsizei>(framebufferSpec.height),
                0,
                // Tell OpenGL the order of the channels
                ToOpenGLColorDataFormat(colorFormat),
                // Tell OpenGL the type of data of the channels
                GL_UNSIGNED_BYTE,
                // No initial pixel data, rendering into the framebuffer will populate the texture
                nullptr
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);

            // Attach the texture to its corresponding framebuffer color attachment point
            auto glColorAttachmentIndex = GL_COLOR_ATTACHMENT0+static_cast<GLenum>(i);
            glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                glColorAttachmentIndex,
                GL_TEXTURE_2D,
                textureColorbuffer, 0
            );
            colorAttachmentIndexes.push_back(glColorAttachmentIndex);
            m_colorAttachments.push_back(textureColorbuffer);
        }

        if (!m_colorAttachments.empty())
        {
            // Tell OpenGL which color attachments should receive fragment shader outputs
            glDrawBuffers(
                static_cast<GLsizei>(colorAttachmentIndexes.size()),
                colorAttachmentIndexes.data()
            );
        }
        else
        {
            // Disable color reading and writing because the framebuffer has no color attachments
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
        }

        if (framebufferSpec.depthStencilFormat != DepthStencilFormat::None)
        {
            GLuint rbo;
            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            glRenderbufferStorage(
                GL_RENDERBUFFER,
                // Tell OpenGL how to store the depth stencils
                ToOpenGLDepthStencilFormat(framebufferSpec.depthStencilFormat),
                static_cast<GLsizei>(framebufferSpec.width),
                static_cast<GLsizei>(framebufferSpec.height)
            );
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glFramebufferRenderbuffer(
                GL_FRAMEBUFFER,
                // Tell the framebuffer what type of attachment the rbo is
                ToOpenGLDepthStencilAttachment(framebufferSpec.depthStencilFormat),
                GL_RENDERBUFFER,
                rbo
            );
            m_rbo = rbo;
        }

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cerr << "Framebuffer creation failed!" << std::endl;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_fbo = fbo;
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        Destroy();
    }

    OpenGLFramebuffer::OpenGLFramebuffer(OpenGLFramebuffer&& other) noexcept :
        m_colorAttachments(std::move(other.m_colorAttachments)),
        m_framebufferSpec(std::move(other.m_framebufferSpec)),
        m_fbo(other.m_fbo),
        m_rbo(other.m_rbo)
    {
        other.m_fbo = 0;
        other.m_rbo = 0;
    }

    OpenGLFramebuffer& OpenGLFramebuffer::operator=(OpenGLFramebuffer&& other) noexcept
    {
        if (this == &other)
            return *this;

        Destroy();
        m_colorAttachments = std::move(other.m_colorAttachments);
        m_framebufferSpec = std::move(other.m_framebufferSpec);
        m_fbo = other.m_fbo;
        m_rbo = other.m_rbo;

        other.m_fbo = 0;
        other.m_rbo = 0;

        return *this;
    }

    void OpenGLFramebuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    }

    void OpenGLFramebuffer::unBind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::resize(const uint32_t width, const uint32_t height)
    {
        if (width == 0 || height == 0 ||
            (m_framebufferSpec.width == width && m_framebufferSpec.height == height))
            return;

        m_framebufferSpec.width = width;
        m_framebufferSpec.height = height;

        for (auto i = 0; i < m_colorAttachments.size(); ++i)
        {
            auto colorFormat = m_framebufferSpec.colorFormats[i];
            auto colorBuffer = m_colorAttachments[i];
            glBindTexture(GL_TEXTURE_2D, colorBuffer);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                static_cast<GLint>(ToOpenGLColorFormat(colorFormat)),
                static_cast<GLsizei>(m_framebufferSpec.width),
                static_cast<GLsizei>(m_framebufferSpec.height),
                0,
                ToOpenGLColorDataFormat(colorFormat),
                GL_UNSIGNED_BYTE,
                nullptr
            );
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        if (m_rbo > 0)
        {
            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
            glRenderbufferStorage(
                GL_RENDERBUFFER,
                ToOpenGLDepthStencilFormat(m_framebufferSpec.depthStencilFormat),
                static_cast<GLsizei>(m_framebufferSpec.width),
                static_cast<GLsizei>(m_framebufferSpec.height)
            );
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }
    }

    void OpenGLFramebuffer::Destroy()
    {
        if (m_fbo > 0)
        {
            glDeleteFramebuffers(1, &m_fbo);
            m_fbo = 0;
        }

        if (!m_colorAttachments.empty())
        {
            for (const auto& colorAttachment : m_colorAttachments)
            {
                glDeleteTextures(1, &colorAttachment);
            }
            m_colorAttachments.clear();
        }

        if (m_rbo > 0)
        {
            glDeleteRenderbuffers(1, &m_rbo);
            m_rbo = 0;
        }
    }
    } // namespace Cocoa::graphics
