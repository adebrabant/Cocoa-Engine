#pragma once

#include "Graphics/GraphicsDevice.hpp"
#include "Core/Memory.hpp"

#include <cstdint>

namespace Cocoa::Graphics
{
	class OpenGLGraphicsDevice : public GraphicsDevice
	{
	public:
		OpenGLGraphicsDevice();
		~OpenGLGraphicsDevice() override;
		void BeginFrame() override;
		void EndFrame() override;
		void SetViewport(uint32_t width, uint32_t height) override;
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void Clear() override;

		Unique<Shader> CreateShader(const std::string& vertexSource, const std::string& fragmentSource) override;
		Unique<VertexArray> CreateVertexArray() override;
		Unique<VertexBuffer> CreateVertexBuffer(const float* vertices, uint32_t size, const BufferLayout& bufferLayout) override;
		Unique<IndexBuffer> CreateIndexBuffer(const uint32_t* indices, uint32_t count) override;
		Unique<Texture2D> CreateTexture2D(TextureSpec textureSpec, const unsigned char* pixels) override;

		void DrawIndexed(const VertexArray& vertexArray, uint32_t indexCount) override;
	};
}