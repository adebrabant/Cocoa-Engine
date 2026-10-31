#pragma once

#include "graphics/Framebuffer.hpp"

namespace cocoa::graphics
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        explicit OpenGLFramebuffer(const FramebufferSpec& framebufferSpec);
        ~OpenGLFramebuffer() override;

        OpenGLFramebuffer(const OpenGLFramebuffer&) = delete;
        OpenGLFramebuffer& operator=(OpenGLFramebuffer&) = delete;

        OpenGLFramebuffer(OpenGLFramebuffer&& other) noexcept;
        OpenGLFramebuffer& operator=(OpenGLFramebuffer&& other) noexcept;

        void bind() const override;
        void unBind() const override;
        void resize(uint32_t width, uint32_t height) override;

    private:
        void Destroy();

    private:
        std::vector<uint32_t> m_colorAttachments;
        FramebufferSpec m_framebufferSpec;
        uint32_t m_fbo;
        uint32_t m_rbo;
    };
}
