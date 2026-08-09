#pragma once

#include "Core/Memory.hpp"
#include "Graphics/GraphicsHandles.hpp"
#include "Math/Vector2f.hpp"
#include "Math/Vector3f.hpp"
#include "Math/Vector4f.hpp"
#include "Math/Matrix4f.hpp"

#include <vector>
#include <array>

namespace Cocoa::Graphics
{
	class IndexBuffer;
	class VertexArray;
	class VertexBuffer;
	class ShaderManager;
	class TextureManager;
	class MaterialManager;
	class GraphicsDevice;
	class OrthographicCamera;

	struct QuadVertex
	{
		Math::Vector3f Position;
		Math::Vector2f TexCoord;
		Math::Vector4f Color;
		// ToDo : Need to look into this
		//float TextureIndex;
		//float TilingFactor;
	};

	struct QuadDrawCommand
	{
		MaterialHandle Material{};
		std::array<QuadVertex, 4> Vertices{};
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

		void BeginScene(const OrthographicCamera& camera);
		void EndScene();
		void DrawQuad(const Math::Matrix4f& modelMatrix, MaterialHandle materialHandle);

	private:
		void Flush();
		void FlushQuadVertices(const MaterialHandle& handle, const std::vector<QuadVertex>& batchVertices) const;

	private:
		GraphicsDevice& m_graphicsDevice;
		ShaderManager& m_shaderManager;
		TextureManager& m_textureManager;
		MaterialManager& m_materialManager;
		Unique<VertexArray> m_vao{ nullptr };
		Unique<VertexBuffer> m_vbo{ nullptr };
		Unique<IndexBuffer> m_ibo{ nullptr };
		Math::Matrix4f m_viewProjectionMatrix{};
		std::vector<QuadDrawCommand> m_quadDrawCommands{};
	};
}
