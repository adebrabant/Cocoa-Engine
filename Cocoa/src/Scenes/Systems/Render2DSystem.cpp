#include "Scenes/Systems/Render2DSystem.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/View.hpp"
#include "Scenes/Components/SpriteComponent.hpp"
#include "Scenes/Components/TransformComponent.hpp"
#include "Scenes/Components/ColorQuadComponent.hpp"
#include "Scenes/Components/QuadComponent.hpp"
#include "Scenes/Components/CircleComponent.hpp"
#include "Scenes/Components/LineComponent.hpp"
#include "Math/Matrix4f.hpp"
#include "Math/Vector4f.hpp"

namespace Cocoa::Scenes
{
	namespace
	{
		void CalculateModelMatrix(
			Math::Matrix4f& modelMatrix,
			const Math::Vector3f& position,
			const float rotation,
			const Math::Vector3f& scale)
		{
			const Math::Matrix4f translation = Math::Matrix4f::Translation(position);
			const Math::Matrix4f zRotation = Math::Matrix4f::RotationZ(rotation);
			const Math::Matrix4f scaleMatrix = Math::Matrix4f::Scale(scale);

			modelMatrix = translation * zRotation * scaleMatrix;
		}
	}

	void Render2DSystem::Update(World& world, float deltaTime)
	{

	}

	void Render2DSystem::BeginRender(World& world, Graphics::Renderer2D& renderer, float alpha)
	{
		
	}

	void Render2DSystem::Render(World& world, Graphics::Renderer2D& renderer, float alpha)
	{
		View<TransformComponent, CircleComponent> circleView(world);
		for (auto [transform, circleComponent] : circleView)
		{
			Math::Matrix4f modelMatrix{};
			CalculateModelMatrix(
				modelMatrix,
				transform.Position,
				transform.Rotation.Z,
				transform.Scale
			);

			renderer.DrawCircle(
				modelMatrix,
				Math::Vector4f(
					circleComponent.Color.R,
					circleComponent.Color.G,
					circleComponent.Color.B,
					circleComponent.Color.A),
				circleComponent.Material,
				circleComponent.Thickness,
				circleComponent.Fade,
				circleComponent.SortingLayer,
				circleComponent.SortingOrder
			);
		}

		View<TransformComponent, ColorQuadComponent> colorQuadView(world);
		for (auto [transform, colorQuadComponent] : colorQuadView)
		{
			Math::Matrix4f modelMatrix{};
			CalculateModelMatrix(
				modelMatrix,
				transform.Position,
				transform.Rotation.Z,
				transform.Scale
			);

			renderer.DrawQuad(
				modelMatrix,
				Math::Vector4f(
					colorQuadComponent.Color.R,
					colorQuadComponent.Color.G,
					colorQuadComponent.Color.B,
					colorQuadComponent.Color.A),
				colorQuadComponent.Material,
				colorQuadComponent.SortingLayer,
				colorQuadComponent.SortingOrder
			);
		}

		View<TransformComponent, QuadComponent> quadView(world);
		for (auto [transform, quadComponent] : quadView)
		{
			Math::Matrix4f modelMatrix{};
			CalculateModelMatrix(
				modelMatrix,
				transform.Position,
				transform.Rotation.Z,
				transform.Scale
			);

			renderer.DrawQuad(
				modelMatrix,
				quadComponent.Material,
				quadComponent.Texture,
				quadComponent.TilingFactor,
				quadComponent.SortingLayer,
				quadComponent.SortingOrder
			);
		}

		View<TransformComponent, SpriteComponent> spriteView(world);
		for (auto [transform, spriteComponent] : spriteView)
		{
			Math::Matrix4f modelMatrix{};
			CalculateModelMatrix(
				modelMatrix,
				transform.Position,
				transform.Rotation.Z,
				transform.Scale
			);

			renderer.DrawQuad(
				modelMatrix,
				spriteComponent.Material,
				spriteComponent.Sprite,
				spriteComponent.TilingFactor,
				spriteComponent.FlipVertical,
				spriteComponent.FlipHorizontal,
				spriteComponent.SortingLayer,
				spriteComponent.SortingOrder
			);
		}

		View<TransformComponent, LineComponent> lineView(world);
		for (auto [transform, lineComponent] : lineView)
		{
			Math::Matrix4f modelMatrix{};
			CalculateModelMatrix(
				modelMatrix,
				transform.Position,
				transform.Rotation.Z,
				transform.Scale
			);

			renderer.DrawLine(
				lineComponent.Material,
				modelMatrix,
				Math::Vector4f(
					lineComponent.Color.R,
					lineComponent.Color.G,
					lineComponent.Color.B,
					lineComponent.Color.A),
				lineComponent.StartPoint,
				lineComponent.EndPoint,
				lineComponent.Thickness,
				lineComponent.Fade,
				lineComponent.SortingLayer,
				lineComponent.SortingOrder
			);
		}
	}
}
