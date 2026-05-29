#pragma once

#include "Graphics/IGraphicsDevice.hpp"

#include <cstdint>

namespace Cocoa::Graphics
{
	class OpenGLShader;
	class OpenGLVertexBuffer;
	class OpenGLVertexArray;
	class OpenGLIndexBuffer;

	class OpenGLGraphicsDevice : public IGraphicsDevice
	{
	public:
		OpenGLGraphicsDevice() = default;
		~OpenGLGraphicsDevice();
		void BeginFrame() override;
		void EndFrame() override;
		void SetViewport(uint32_t width, uint32_t height) override;
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void Clear() override;

		// Temporary rendering checkpoint
		// Remove once Shader / VertexBuffer / VertexArray abstractions exist
		void RenderTemp();

	private:
		void InitTemp();

	private:
		OpenGLShader* m_shader;
		OpenGLVertexBuffer* m_vbo;
		OpenGLVertexArray* m_vao;
		OpenGLIndexBuffer* m_ibo;
		bool m_isTempTriangleInit = false;
	};
}