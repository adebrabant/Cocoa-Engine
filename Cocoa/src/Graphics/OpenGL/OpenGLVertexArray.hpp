#pragma once

#include "Graphics/VertexArray.hpp"

#include <cstdint>

namespace Cocoa::Graphics
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

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const VertexBuffer& vertexBuffer) override;
		void SetIndexBuffer(const IndexBuffer& indexBuffer) override;

	private:
		void Destroy();

	private:
		uint32_t m_vao;
	};
}