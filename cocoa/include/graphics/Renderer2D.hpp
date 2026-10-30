#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "graphics/QuadBatch.hpp"
#include "graphics/RenderStatistics.hpp"
#include "graphics/SortLayer.hpp"
#include "graphics/Viewport.hpp"
#include "math/Matrix4f.hpp"

#include <variant>

namespace cocoa::Graphics
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

		void BeginDraw(const Math::Matrix4f& viewProjectionMatrix);
		void DrawQuad(
			const Math::Matrix4f& modelMatrix,
			MaterialHandle materialHandle,
			TextureHandle textureHandle,
			const Math::Vector2f& tilingFactor,
			SortLayer sortingLayer,
			int sortingOrder);

		void DrawQuad(
			const Math::Matrix4f& modelMatrix,
			MaterialHandle materialHandle,
			SpriteHandle spriteHandle,
			const Math::Vector2f& tilingFactor,
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
			Math::Matrix4f ModelMatrix{};
			MaterialHandle Material{};
			TextureHandle Texture{};
			Math::Vector2f TilingFactor{};
		};
		struct SpriteDrawSubmission
		{
			Math::Matrix4f ModelMatrix{};
			MaterialHandle Material{};
			SpriteHandle Sprite{};
			Math::Vector2f TilingFactor{};
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
		Math::Matrix4f m_viewProjectionMatrix;
	};
}
