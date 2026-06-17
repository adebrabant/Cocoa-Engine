#pragma once

#include <Graphics/GraphicsDevice.hpp>

namespace Cocoa::Stubs
{
	class StubGraphicsDevice : public Graphics::GraphicsDevice
	{
	public:
		StubGraphicsDevice() = default;
		~StubGraphicsDevice() = default;
		void BeginFrame() override;
		void EndFrame() override;
		void SetViewport(uint32_t width, uint32_t height) override;
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void Clear() override;
		Unique<Graphics::Shader> CreateShader(const std::string& vertexSource, const std::string& fragmentSource) override;
		Unique<Graphics::VertexArray> CreateVertexArray() override;
		Unique<Graphics::VertexBuffer> CreateVertexBuffer(const float* vertices, uint32_t size, const Graphics::BufferLayout& bufferLayout) override;
		Unique<Graphics::IndexBuffer> CreateIndexBuffer(const uint32_t* indices, uint32_t count) override;
		Unique<Graphics::Texture2D> CreateTexture2D(Graphics::TextureSpec textureSpec, const unsigned char* pixels) override;
		void DrawIndexed(const Graphics::VertexArray& vertexArray, uint32_t indexCount) override;
	};
}