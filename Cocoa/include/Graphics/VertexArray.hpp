#pragma once

namespace Cocoa::Graphics
{
	class IndexBuffer;
	class VertexBuffer;

	class VertexArray 
	{
	public:
		virtual ~VertexArray() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const VertexBuffer& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const IndexBuffer& indexBuffer) = 0;
	};
}