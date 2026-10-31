#include "scenes/systems/Render2DSystem.hpp"
#include "graphics/Renderer2D.hpp"
#include "math/Matrix4f.hpp"
#include "scenes/components/QuadComponent.hpp"
#include "scenes/components/SpriteComponent.hpp"
#include "scenes/components/TransformComponent.hpp"
#include "scenes/ecs/View.hpp"
#include "scenes/ecs/World.hpp"

namespace cocoa::scenes
{
	void Render2DSystem::Update(World& world, float deltaTime)
	{

	}

	void Render2DSystem::BeginRender(World& world, graphics::Renderer2D& renderer, float alpha)
	{

	}

	void Render2DSystem::Render(World& world, graphics::Renderer2D& renderer, float alpha)
	{
		View<TransformComponent, QuadComponent> quadView(world);
		for (auto [transform, quadComponent] : quadView)
		{
			math::Matrix4f translation = math::Matrix4f::Translation(transform.Position);
			math::Matrix4f zRotation = math::Matrix4f::RotationZ(transform.Rotation.Z);
			math::Matrix4f scale = math::Matrix4f::Scale(transform.Scale);

			math::Matrix4f modelMatrix = translation * zRotation * scale;
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
			math::Matrix4f translation = math::Matrix4f::Translation(transform.Position);
			math::Matrix4f zRotation = math::Matrix4f::RotationZ(transform.Rotation.Z);
			math::Matrix4f scale = math::Matrix4f::Scale(transform.Scale);

			math::Matrix4f modelMatrix = translation * zRotation * scale;
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
	}
}
