#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "graphics/QuadBatch.hpp"
#include "graphics/RenderStatistics.hpp"
#include "graphics/SortLayer.hpp"
#include "graphics/Viewport.hpp"
#include "math/Matrix4f.hpp"

#include <variant>

namespace cocoa::graphics
{
	class GraphicsDevice;
	class ShaderManager;
	class TextureManager;
	class MaterialManager;
	class SpriteManager;

	class Renderer2D
	{
	public:
		Renderer2D(
			GraphicsDevice& graphicsDevice,
			ShaderManager& shaderManager,
			TextureManager& textureManager,
			MaterialManager& materialManager,
			SpriteManager& spriteManager
		);
		~Renderer2D();

		void BeginDraw(const math::Matrix4f& viewProjectionMatrix);
		void DrawQuad(
			const math::Matrix4f& modelMatrix,
			MaterialHandle materialHandle,
			TextureHandle textureHandle,
			const math::Vector2f& tilingFactor,
			SortLayer sortingLayer,
			int sortingOrder);

		void DrawQuad(
			const math::Matrix4f& modelMatrix,
			MaterialHandle materialHandle,
			SpriteHandle spriteHandle,
			const math::Vector2f& tilingFactor,
			bool flipVertical,
			bool flipHorizontal,
			SortLayer sortingLayer,
			int sortingOrder
		);
		void EndDraw();

		[[nodiscard]] const RenderStatistics& GetRenderStatistics() const { return m_renderStatistics; }
		[[nodiscard]] const Viewport& GetViewport() const;

	private:
		enum class BatchType
		{
			Quad
		};
		struct QuadDrawSubmission
		{
			math::Matrix4f ModelMatrix{};
			MaterialHandle Material{};
			TextureHandle Texture{};
			math::Vector2f TilingFactor{};
		};
		struct SpriteDrawSubmission
		{
			math::Matrix4f ModelMatrix{};
			MaterialHandle Material{};
			SpriteHandle Sprite{};
			math::Vector2f TilingFactor{};
			bool FlipVertical{};
			bool FlipHorizontal{};
		};
		struct DrawSubmission
		{
			SortLayer SortingLayer{};
			int SortingOrder{};
			BatchType Batch{};
			std::variant<
				QuadDrawSubmission,
				SpriteDrawSubmission> Data;
		};

	private:
		std::vector<DrawSubmission> m_drawSubmissions;
		RenderStatistics m_renderStatistics;
		GraphicsDevice& m_graphicsDevice;
		QuadBatch m_quadBatch;
		math::Matrix4f m_viewProjectionMatrix;
	};
}
