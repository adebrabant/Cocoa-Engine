#pragma once

#include "Graphics/Framebuffer.hpp"

namespace Cocoa::Graphics
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

        void Bind() const override;
        void UnBind() const override;
        void SetFramebufferSpec(const FramebufferSpec& spec);

    private:
        void Destroy();

    private:
        std::vector<uint32_t> m_colorAttachments;
        FramebufferSpec m_framebufferSpec;
        uint32_t m_fbo;
    };
}
