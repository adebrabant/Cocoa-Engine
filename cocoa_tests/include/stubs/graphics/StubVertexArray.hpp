#pragma once

#include <graphics/VertexArray.hpp>

namespace cocoa_tests::stubs
{
    class StubVertexArray : public cocoa::graphics::VertexArray
    {
    public:
        ~StubVertexArray() override = default;
        void bind() const override;
        void unbind() const override;
        void addVertexBuffer(const cocoa::graphics::VertexBuffer &vertexBuffer) override;
        void setIndexBuffer(const cocoa::graphics::IndexBuffer &indexBuffer) override;
    };
}
