#include "Graphics/Renderer2D.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/GraphicsDevice.hpp"

namespace Cocoa::Graphics
{
	Renderer2D::Renderer2D(
		GraphicsDevice& graphicsDevice,
		ShaderManager& shaderManager,
		TextureManager& textureManager,
		MaterialManager& materialManager
	) :
		m_renderStatistics(),
		m_quadBatch(
			graphicsDevice,
			shaderManager,
			textureManager,
			materialManager,
			m_renderStatistics),
		m_viewProjectionMatrix()
	{

	}

	Renderer2D::~Renderer2D() = default;

	void Renderer2D::BeginDraw(const Math::Matrix4f& viewProjectionMatrix)
	{
		m_renderStatistics.Reset();
		m_viewProjectionMatrix = viewProjectionMatrix;
	}

	void Renderer2D::DrawQuad(const Math::Matrix4f& modelMatrix, const MaterialHandle materialHandle)
	{
		m_quadBatch.Draw(modelMatrix, materialHandle);
	}

	void Renderer2D::EndDraw()
	{
		m_quadBatch.Flush(m_viewProjectionMatrix);
	}
}
