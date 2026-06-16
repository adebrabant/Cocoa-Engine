#pragma once

#include "Core/Memory.hpp"
#include "Graphics/GraphicsDevice.hpp"

// ToDo: Remove after DrawQuad is added
#include "Assets/AssetManager.hpp"
#include "Assets/AssetDatabase.hpp"

namespace Cocoa::Graphics
{
	class Shader;
	class IndexBuffer;
	class VertexArray;
	class VertexBuffer;
	class Texture2D;
	class ShaderManager;
	class TextureManager;

	class Renderer2D
	{
	public:
		Renderer2D(
			GraphicsDevice& graphicsDevice, 
			ShaderManager& shaderManager, 
			TextureManager& textureManager, 
			Assets::AssetManager& assetManager, 
			Assets::AssetDatabase& assetDatabase
		);
		~Renderer2D();

		void BeginScene();
		void EndScene();

	private:
		void Flush();

	private:
		GraphicsDevice& m_graphicsDevice;
		ShaderManager& m_shaderManager;
		TextureManager& m_textureManager;

		//ToDo: Remove after DrawQuad is added
		Assets::AssetManager& m_tempAssetManager;
		Assets::AssetDatabase& m_tempAssetDatabase;
		
		const Shader* m_shader{ nullptr };
		Unique<VertexArray> m_vao{ nullptr };
		Unique<VertexBuffer> m_vbo{ nullptr };
		Unique<IndexBuffer> m_ibo{ nullptr };
		const Texture2D* m_texture{ nullptr };
	};
}