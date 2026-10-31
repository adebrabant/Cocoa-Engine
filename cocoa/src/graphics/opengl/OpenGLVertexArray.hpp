#pragma once

#include "graphics/VertexArray.hpp"

#include <cstdint>

namespace cocoa::graphics
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		OpenGLVertexArray(const OpenGLVertexArray&) = delete;
		OpenGLVertexArray& operator=(const OpenGLVertexArray&) = delete;

		OpenGLVertexArray(OpenGLVertexArray&& other) noexcept;
		OpenGLVertexArray& operator=(OpenGLVertexArray&& other) noexcept;

		void bind() const override;
		void unbind() const override;

		void addVertexBuffer(const VertexBuffer& vertexBuffer) override;
		void setIndexBuffer(const IndexBuffer& indexBuffer) override;

	private:
		void Destroy() const;

	private:
		uint32_t m_vao;
	};
}
