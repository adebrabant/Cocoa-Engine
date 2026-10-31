#include "graphics/Renderer2D.hpp"
#include "graphics/GraphicsDevice.hpp"
#include "graphics/MaterialManager.hpp"
#include "graphics/ShaderManager.hpp"
#include "graphics/SpriteManager.hpp"
#include "graphics/TextureManager.hpp"

#include <algorithm>

namespace cocoa::graphics
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
		m_graphicsDevice(graphicsDevice),
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

	void Renderer2D::BeginDraw(const math::Matrix4f& viewProjectionMatrix)
	{
		m_renderStatistics.Reset();
		m_drawSubmissions.clear();
		m_viewProjectionMatrix = viewProjectionMatrix;
	}

	void Renderer2D::DrawQuad(
		const math::Matrix4f& modelMatrix,
		const MaterialHandle materialHandle,
		const TextureHandle textureHandle,
		const math::Vector2f& tilingFactor,
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
		const math::Matrix4f& modelMatrix,
		const MaterialHandle materialHandle,
		const SpriteHandle spriteHandle,
		const math::Vector2f& tilingFactor,
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

		struct SortedDrawSubmission
		{
			SortLayer SortingLayer;
			int SortingOrder;
			size_t Index;
		};

		std::vector<SortedDrawSubmission> sortedDrawSubmissions;
		sortedDrawSubmissions.reserve(m_drawSubmissions.size());

		for (auto i = 0; i < m_drawSubmissions.size(); ++i)
		{
			sortedDrawSubmissions.emplace_back(
				m_drawSubmissions[i].SortingLayer,
				m_drawSubmissions[i].SortingOrder,
				i
			);
		}

		std::stable_sort(sortedDrawSubmissions.begin(), sortedDrawSubmissions.end(),
			[](const SortedDrawSubmission& a, const SortedDrawSubmission& b)
			{
				if (a.SortingLayer != b.SortingLayer)
				{
					return a.SortingLayer < b.SortingLayer;
				}

				return a.SortingOrder < b.SortingOrder;
			});

		for (size_t i = 0; i < sortedDrawSubmissions.size(); ++i)
		{
			const auto& drawSubmission = m_drawSubmissions[sortedDrawSubmissions[i].Index];
			if (const auto* quadData = std::get_if<QuadDrawSubmission>(&drawSubmission.Data))
			{
				m_quadBatch.Draw(
					quadData->ModelMatrix,
					quadData->Material,
					quadData->Texture,
					quadData->TilingFactor
				);
			}
			else if (const auto* spriteData = std::get_if<SpriteDrawSubmission>(&drawSubmission.Data))
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
				drawSubmission.Batch != m_drawSubmissions[sortedDrawSubmissions[i+1].Index].Batch)
			{
				switch (drawSubmission.Batch)
				{
				case BatchType::Quad:
					m_quadBatch.Flush(m_viewProjectionMatrix);
					break;
				}
			}
		}
	}

	const Viewport& Renderer2D::GetViewport() const
	{
		return m_graphicsDevice.GetViewport();
	}
}
