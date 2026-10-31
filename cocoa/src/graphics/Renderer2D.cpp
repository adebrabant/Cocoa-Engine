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

	void Renderer2D::beginDraw(const math::Matrix4f& viewProjectionMatrix)
	{
		m_renderStatistics.reset();
		m_drawSubmissions.clear();
		m_viewProjectionMatrix = viewProjectionMatrix;
	}

	void Renderer2D::drawQuad(
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

	void Renderer2D::drawQuad(
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

	void Renderer2D::endDraw()
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
				m_drawSubmissions[i].sortingLayer,
				m_drawSubmissions[i].sortingOrder,
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
			if (const auto* quadData = std::get_if<QuadDrawSubmission>(&drawSubmission.data))
			{
				m_quadBatch.draw(
					quadData->modelMatrix,
					quadData->materialHandle,
					quadData->textureHandle,
					quadData->tilingFactor
				);
			}
			else if (const auto* spriteData = std::get_if<SpriteDrawSubmission>(&drawSubmission.data))
			{
				m_quadBatch.draw(
					spriteData->modelMatrix,
					spriteData->materialHandle,
					spriteData->spriteHandle,
					spriteData->tilingFactor,
					spriteData->flipVertical,
					spriteData->flipHorizontal
				);
			}

			if (i == m_drawSubmissions.size() - 1 ||
				drawSubmission.batchType != m_drawSubmissions[sortedDrawSubmissions[i+1].Index].batchType)
			{
				switch (drawSubmission.batchType)
				{
				case BatchType::Quad:
					m_quadBatch.flush(m_viewProjectionMatrix);
					break;
				}
			}
		}
	}

	const Viewport& Renderer2D::getViewport() const
	{
		return m_graphicsDevice.getViewport();
	}
}
