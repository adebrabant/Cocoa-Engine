#pragma once

#include "Graphics/IGraphicsDevice.hpp"
#include <cstdint>

namespace VexEngine::Graphics
{
	class OpenGLGraphicsDevice : public IGraphicsDevice
	{
	public:
		OpenGLGraphicsDevice() = default;
		~OpenGLGraphicsDevice() = default;
		void BeginFrame() override;
		void EndFrame() override;
		void SetViewport(uint32_t width, uint32_t height) override;
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void Clear() override;

		// Temporary rendering checkpoint
		// Remove once Shader / VertexBuffer / VertexArray abstractions exist
		void RenderTempTriangle();

	private:
		void InitTempTriangle();

	private:
		bool m_isTempTriangleInit = false;
		uint32_t m_tempTriangleShaderProgram = 0;
		uint32_t m_tempTriangleVertexArray = 0;
		uint32_t m_tempTriangleVertexBuffer = 0;
	};
}