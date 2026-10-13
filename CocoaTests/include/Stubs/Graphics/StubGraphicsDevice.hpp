#pragma once

#include <Graphics/GraphicsDevice.hpp>

namespace CocoaTests::Stubs
{
	class StubGraphicsDevice : public Cocoa::Graphics::GraphicsDevice
	{
	public:
		StubGraphicsDevice() = default;
		~StubGraphicsDevice() override = default;
		void BeginFrame() override;
		void EndFrame() override;
		void SetBlendMode(Cocoa::Graphics::BlendMode mode) override;
		void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void Clear() override;
		Cocoa::Unique<Cocoa::Graphics::Shader> CreateShader(const std::string& vertexSource, const std::string& fragmentSource) override;
		Cocoa::Unique<Cocoa::Graphics::VertexArray> CreateVertexArray() override;
		Cocoa::Unique<Cocoa::Graphics::VertexBuffer> CreateVertexBuffer(uint32_t size, const Cocoa::Graphics::BufferLayout& bufferLayout) override;
		Cocoa::Unique<Cocoa::Graphics::VertexBuffer> CreateVertexBuffer(const void* vertices, uint32_t size, const Cocoa::Graphics::BufferLayout& bufferLayout) override;
		Cocoa::Unique<Cocoa::Graphics::IndexBuffer> CreateIndexBuffer(const uint32_t* indices, uint32_t count) override;
		Cocoa::Unique<Cocoa::Graphics::Texture2D> CreateTexture2D(Cocoa::Graphics::TextureSpec textureSpec, const unsigned char* pixels) override;
		void DrawIndexed(const Cocoa::Graphics::VertexArray& vertexArray, uint32_t indexCount) override;
	};
}