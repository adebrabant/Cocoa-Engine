#pragma once

namespace Cocoa::Graphics
{
	class BufferLayout;

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetData(const void* data, uint32_t size) const = 0;
		[[nodiscard]] virtual const BufferLayout& GetLayout() const = 0;
	};
}