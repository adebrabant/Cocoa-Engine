#pragma once

#include "Math/Matrix4f.hpp"
#include "Graphics/QuadBatch.hpp"
#include "Graphics/GraphicsHandles.hpp"
#include "Graphics/RenderStatistics.hpp"

namespace Cocoa::Graphics
{
	class GraphicsDevice;
	class ShaderManager;
	class TextureManager;
	class MaterialManager;

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

		void BeginDraw(const Math::Matrix4f& viewProjectionMatrix);
		void DrawQuad(const Math::Matrix4f& modelMatrix, MaterialHandle materialHandle);
		void EndDraw();

	private:
		RenderStatistics m_renderStatistics;
		QuadBatch m_quadBatch;
		Math::Matrix4f m_viewProjectionMatrix;
	};
}
