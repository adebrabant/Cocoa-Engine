#pragma once

#include <graphics/VertexArray.hpp>

namespace cocoa_benchmarks
{
    class StubVertexArray : public cocoa::graphics::VertexArray
    {
    public:
        ~StubVertexArray() override = default;
        void Bind() const override { }
        void Unbind() const override { }
        void AddVertexBuffer(const cocoa::graphics::VertexBuffer& vertexBuffer) override { }
        void SetIndexBuffer(const cocoa::graphics::IndexBuffer& indexBuffer) override { }
    };
}
