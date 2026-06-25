#pragma once

#include "Core/Memory.hpp"
#include "Graphics/GraphicsHandles.hpp"

#include <vector>

namespace Cocoa::Graphics
{
	class IndexBuffer;
	class VertexArray;
	class VertexBuffer;
	class ShaderManager;
	class TextureManager;
	class MaterialManager;
	class GraphicsDevice;

	struct DrawCommand2D
	{
		MaterialHandle Material;
	};

	class Renderer2D
	{
	public:
		Renderer2D(
			GraphicsDevice& graphicsDevice, 
			ShaderManager& shaderManager, 
			TextureManager& textureManager, 
			MaterialManager& materialManager
		);
		~Renderer2D();

		void BeginScene();
		void EndScene();
		void DrawQuad(MaterialHandle materialHandle);

	private:
		void Flush();

	private:
		GraphicsDevice& m_graphicsDevice;
		ShaderManager& m_shaderManager;
		TextureManager& m_textureManager;
		MaterialManager& m_materialManager;
		Unique<VertexArray> m_vao{ nullptr };
		Unique<VertexBuffer> m_vbo{ nullptr };
		Unique<IndexBuffer> m_ibo{ nullptr };
		std::vector<DrawCommand2D> m_drawCommands;
	};
}