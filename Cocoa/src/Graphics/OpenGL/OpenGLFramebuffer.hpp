#pragma once

#include "Graphics/Framebuffer.hpp"

namespace Cocoa::Graphics
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        explicit OpenGLFramebuffer(FramebufferSpec framebufferSpec);
        ~OpenGLFramebuffer() override;

        OpenGLFramebuffer(const OpenGLFramebuffer&) = delete;
        OpenGLFramebuffer& operator=(OpenGLFramebuffer&& other) = delete;

        OpenGLFramebuffer(OpenGLFramebuffer&& other) noexcept;
        OpenGLFramebuffer& operator==(OpenGLFramebuffer&& other) noexcept;

        void Bind() const override;
        void UnBind() const override;

    private:
        void Destroy() const;

    private:
        FramebufferSpec m_framebufferSpec;
        uint32_t m_fbo;
    };
}
