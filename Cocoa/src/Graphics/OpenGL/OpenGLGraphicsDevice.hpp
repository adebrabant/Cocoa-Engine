#pragma once

#include "Graphics/IGraphicsDevice.hpp"

#include <cstdint>

// Temp for image loading remove after tests
namespace Cocoa::Assets
{
	class AssetManager;
}

namespace Cocoa::Graphics
{
	class OpenGLShader;
	class OpenGLVertexBuffer;
	class OpenGLVertexArray;
	class OpenGLIndexBuffer;
	class OpenGLTexture2D;

	class OpenGLGraphicsDevice : public IGraphicsDevice
	{
	public:
		OpenGLGraphicsDevice();
		~OpenGLGraphicsDevice();
		void BeginFrame() override;
		void EndFrame() override;
		void SetViewport(uint32_t width, uint32_t height) override;
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void Clear() override;

		// Temporary rendering checkpoint
		// Remove once Shader / VertexBuffer / VertexArray abstractions exist
		void InitTemp(Cocoa::Assets::AssetManager assetManager);
		void RenderTemp();

	private:

	private:
		OpenGLShader* m_shader{ nullptr };
		OpenGLVertexBuffer* m_vbo{ nullptr };
		OpenGLVertexArray* m_vao{ nullptr };
		OpenGLIndexBuffer* m_ibo{ nullptr };
		OpenGLTexture2D* m_texture{ nullptr };
	};
}