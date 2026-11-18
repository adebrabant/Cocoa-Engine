#pragma once

#include "Math/Matrix4f.hpp"
#include "Graphics/QuadBatch.hpp"
#include "Graphics/CircleBatch.hpp"
#include "Graphics/SortLayer.hpp"
#include "Graphics/GraphicsHandles.hpp"
#include "Graphics/RenderStatistics.hpp"
#include "Graphics/Viewport.hpp"

#include <variant>

#include "Scenes/Components/CircleComponent.hpp"

namespace Cocoa::Graphics
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
			const Math::Vector4f& color,
			MaterialHandle materialHandle,
			SortLayer sortingLayer,
			int sortingOrder
		);
		void DrawQuad(
			const Math::Matrix4f& modelMatrix,
			MaterialHandle materialHandle,
			TextureHandle textureHandle,
			const Math::Vector2f& tilingFactor,
			SortLayer sortingLayer,
			int sortingOrder
		);
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
		void DrawCircle(
			const Math::Matrix4f& modelMatrix,
			const Math::Vector4f& color,
			MaterialHandle materialHandle,
			float thickness,
			float fade,
			SortLayer sortingLayer,
			int sortingOrder
		);
		void EndDraw();

		[[nodiscard]] const RenderStatistics& GetRenderStatistics() const { return m_renderStatistics; }
		[[nodiscard]] const Viewport& GetViewport() const;

	private:
		enum class BatchType
		{
			Quad,
			Circle
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
		struct ColorQuadDrawSubmission
		{
			Math::Matrix4f ModelMatrix{};
			Math::Vector4f Color{};
			MaterialHandle Material{};
		};
		struct CircleDrawSubmission
		{
			Math::Matrix4f ModelMatrix{};
			Math::Vector4f Color{};
			MaterialHandle Material{};
			float Thickness{};
			float Fade{};
		};
		struct DrawSubmission
		{
			SortLayer SortingLayer{};
			int SortingOrder{};
			BatchType Batch{};
			std::variant<
				QuadDrawSubmission,
				SpriteDrawSubmission,
				ColorQuadDrawSubmission,
				CircleDrawSubmission> Data;
		};
	
	private:
		std::vector<DrawSubmission> m_drawSubmissions;
		RenderStatistics m_renderStatistics;
		GraphicsDevice& m_graphicsDevice;
		QuadBatch m_quadBatch;
		CircleBatch m_circleBatch;
		Math::Matrix4f m_viewProjectionMatrix;
	};
}
