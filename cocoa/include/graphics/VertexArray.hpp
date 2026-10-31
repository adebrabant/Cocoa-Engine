#pragma once

namespace cocoa::graphics
{
	class IndexBuffer;
	class VertexBuffer;

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void addVertexBuffer(const VertexBuffer& vertexBuffer) = 0;
		virtual void setIndexBuffer(const IndexBuffer& indexBuffer) = 0;
	};
}
