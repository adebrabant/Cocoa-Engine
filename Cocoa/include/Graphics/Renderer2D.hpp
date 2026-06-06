#pragma once

#include "Core/Memory.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Assets/AssetManager.hpp"

namespace Cocoa::Graphics
{
	class Shader;
	class IndexBuffer;
	class VertexArray;
	class VertexBuffer;
	class Texture2D;

	class Renderer2D
	{
	public:
		Renderer2D(GraphicsDevice& graphicsDevice, Assets::AssetManager& assetManager);
		~Renderer2D();
		void BeginScene();
		void EndScene();

	private:
		void Flush();

	private:
		GraphicsDevice& m_graphicsDevice;
		Assets::AssetManager& m_tempAssetManager;
		Unique<Shader> m_shader{ nullptr };
		Unique<VertexArray> m_vao{ nullptr };
		Unique<VertexBuffer> m_vbo{ nullptr };
		Unique<IndexBuffer> m_ibo{ nullptr };
		Unique<Texture2D> m_texture{ nullptr };
	};
}