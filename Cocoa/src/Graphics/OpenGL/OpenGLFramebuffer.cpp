#include "Graphics/OpenGL/OpenGLFramebuffer.hpp"

#include <stdexcept>
#include <GL/glew.h>

namespace Cocoa::Graphics
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec framebufferSpec) :
        m_framebufferSpec(framebufferSpec),
        m_fbo(0)
    {
        GLuint fbo{0};
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER)
        {
            throw std::runtime_error("Framebuffer creation failed!");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_fbo = fbo;
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        Destroy();
    }

    OpenGLFramebuffer::OpenGLFramebuffer(OpenGLFramebuffer&& other) noexcept :
        m_framebufferSpec(other.m_framebufferSpec),
        m_fbo(other.m_fbo)
    {
        other.m_fbo = 0;
    }

    OpenGLFramebuffer& OpenGLFramebuffer::operator==(OpenGLFramebuffer&& other) noexcept
    {
        if (this == &other)
            return *this;

        Destroy();
        m_framebufferSpec = other.m_framebufferSpec;
        m_fbo = other.m_fbo;
        other.m_fbo = 0;

        return *this;
    }

    void OpenGLFramebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    }

    void OpenGLFramebuffer::UnBind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Destroy() const
    {
        if (m_fbo <= 0)
            return;

        glDeleteFramebuffers(1, &m_fbo);
    }
}
