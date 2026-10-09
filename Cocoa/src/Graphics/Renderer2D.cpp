#include "Graphics/Renderer2D.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/SpriteManager.hpp"
#include "Graphics/GraphicsDevice.hpp"

#include <algorithm>

namespace Cocoa::Graphics
{
	Renderer2D::Renderer2D(
		GraphicsDevice& graphicsDevice,
		ShaderManager& shaderManager,
		TextureManager& textureManager,
		MaterialManager& materialManager,
		SpriteManager& spriteManager
	) :
		m_drawSubmissions(),
		m_renderStatistics(),
		m_quadBatch(
			graphicsDevice,
			shaderManager,
			textureManager,
			materialManager,
			spriteManager,
			m_renderStatistics),
		m_viewProjectionMatrix()
	{

	}

	Renderer2D::~Renderer2D() = default;

	void Renderer2D::BeginDraw(const Math::Matrix4f& viewProjectionMatrix)
	{
		m_renderStatistics.Reset();
		m_drawSubmissions.clear();
		m_viewProjectionMatrix = viewProjectionMatrix;
	}

	void Renderer2D::DrawQuad(
		const Math::Matrix4f& modelMatrix,
		const MaterialHandle materialHandle,
		const TextureHandle textureHandle,
		const Math::Vector2f& tilingFactor,
		const SortLayer sortingLayer,
		const int sortingOrder)
	{
		m_drawSubmissions.emplace_back(
			sortingLayer,
			sortingOrder,
			BatchType::Quad,
			QuadDrawSubmission {
				modelMatrix,
				materialHandle,
				textureHandle,
				tilingFactor }
		);
	}

	void Renderer2D::DrawQuad(
		const Math::Matrix4f& modelMatrix,
		const MaterialHandle materialHandle,
		const SpriteHandle spriteHandle,
		const Math::Vector2f& tilingFactor,
		const bool flipVertical,
		const bool flipHorizontal,
		const SortLayer sortingLayer,
		const int sortingOrder)
	{
		m_drawSubmissions.emplace_back(
			sortingLayer,
			sortingOrder,
			BatchType::Quad,
			SpriteDrawSubmission {
				modelMatrix,
				materialHandle,
				spriteHandle,
				tilingFactor,
				flipVertical,
				flipHorizontal }
		);
	}

	void Renderer2D::EndDraw()
	{
		if (m_drawSubmissions.empty())
			return;

		std::stable_sort(m_drawSubmissions.begin(), m_drawSubmissions.end(),
			[](const DrawSubmission& a, const DrawSubmission& b)
			{
				if (a.SortingLayer != b.SortingLayer)
				{
					return a.SortingLayer < b.SortingLayer;
				}

				return a.SortingOrder < b.SortingOrder;
			});

		for (size_t i = 0; i < m_drawSubmissions.size(); ++i)
		{
			if (const auto* quadData = std::get_if<QuadDrawSubmission>(&m_drawSubmissions[i].Data))
			{
				m_quadBatch.Draw(
					quadData->ModelMatrix,
					quadData->Material,
					quadData->Texture,
					quadData->TilingFactor
				);

				if (i == m_drawSubmissions.size() - 1 ||
					m_drawSubmissions[i].Batch != m_drawSubmissions[i+1].Batch)
				{
					m_quadBatch.Flush(m_viewProjectionMatrix);
				}
			}
			else if (const auto* spriteData = std::get_if<SpriteDrawSubmission>(&m_drawSubmissions[i].Data))
			{
				m_quadBatch.Draw(
					spriteData->ModelMatrix,
					spriteData->Material,
					spriteData->Sprite,
					spriteData->TilingFactor,
					spriteData->FlipVertical,
					spriteData->FlipHorizontal
				);
			}

			if (i == m_drawSubmissions.size() - 1 ||
				m_drawSubmissions[i].Batch != m_drawSubmissions[i+1].Batch)
			{
				switch (m_drawSubmissions[i].Batch)
				{
				case BatchType::Quad:
					m_quadBatch.Flush(m_viewProjectionMatrix);
					break;
				}
			}
		}
	}
}
