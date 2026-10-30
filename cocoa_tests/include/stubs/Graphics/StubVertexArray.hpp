#pragma once

#include <graphics/VertexArray.hpp>

namespace CocoaTests::Stubs
{
    class StubVertexArray : public cocoa::Graphics::VertexArray
    {
    public:
        ~StubVertexArray() override = default;
        void Bind() const override;
        void Unbind() const override;
        void AddVertexBuffer(const cocoa::Graphics::VertexBuffer &vertexBuffer) override;
        void SetIndexBuffer(const cocoa::Graphics::IndexBuffer &indexBuffer) override;
    };
}