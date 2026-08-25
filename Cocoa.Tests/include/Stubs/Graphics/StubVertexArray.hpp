#pragma once

#include <Graphics/VertexArray.hpp>

namespace Cocoa::Stubs
{
    class StubVertexArray : public Cocoa::Graphics::VertexArray
    {
    public:
        ~StubVertexArray() override = default;
        void Bind() const override;
        void Unbind() const override;
        void AddVertexBuffer(const Cocoa::Graphics::VertexBuffer &vertexBuffer) override;
        void SetIndexBuffer(const Cocoa::Graphics::IndexBuffer &indexBuffer) override;
    };
}