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
	void Render2DSystem::update(World& world, float deltaTime)
	{

	}

	void Render2DSystem::beginRender(World& world, graphics::Renderer2D& renderer, float alpha)
	{

	}

	void Render2DSystem::render(World& world, graphics::Renderer2D& renderer, float alpha)
	{
		View<TransformComponent, QuadComponent> quadView(world);
		for (auto [transform, quadComponent] : quadView)
		{
			math::Matrix4f translation = math::Matrix4f::translation(transform.position);
			math::Matrix4f zRotation = math::Matrix4f::rotationZ(transform.rotation.z);
			math::Matrix4f scale = math::Matrix4f::scale(transform.scale);

			math::Matrix4f modelMatrix = translation * zRotation * scale;
			renderer.drawQuad(
				modelMatrix,
				quadComponent.materialHandle,
				quadComponent.textureHandle,
				quadComponent.tilingFactor,
				quadComponent.sortingLayer,
				quadComponent.sortingOrder
			);
		}

		View<TransformComponent, SpriteComponent> spriteView(world);
		for (auto [transform, spriteComponent] : spriteView)
		{
			math::Matrix4f translation = math::Matrix4f::translation(transform.position);
			math::Matrix4f zRotation = math::Matrix4f::rotationZ(transform.rotation.z);
			math::Matrix4f scale = math::Matrix4f::scale(transform.scale);

			math::Matrix4f modelMatrix = translation * zRotation * scale;
			renderer.drawQuad(
				modelMatrix,
				spriteComponent.materialHandle,
				spriteComponent.spriteHandle,
				spriteComponent.tilingFactor,
				spriteComponent.flipVertical,
				spriteComponent.flipHorizontal,
				spriteComponent.sortingLayer,
				spriteComponent.sortingOrder
			);
		}
	}
}
