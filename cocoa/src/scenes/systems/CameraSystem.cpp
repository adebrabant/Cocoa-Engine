#include "scenes/systems/CameraSystem.hpp"
#include "graphics/OrthographicProjection.hpp"
#include "graphics/Renderer2D.hpp"
#include "scenes/components/CameraComponent.hpp"
#include "scenes/components/ProjectionComponent.hpp"
#include "scenes/components/TransformComponent.hpp"
#include "scenes/ecs/View.hpp"
#include "scenes/ecs/World.hpp"

namespace cocoa::scenes
{
	void CameraSystem::update(World& world, float deltaTime)
	{

	}

	// TODO: Look into fallback or required components if not found
	void CameraSystem::beginRender(World& world, graphics::Renderer2D& renderer, float alpha)
	{
		View<TransformComponent, CameraComponent, ProjectionComponent> view(world);

		for (auto [transformComponent, cameraComponent, projectionComponent] : view)
		{
			// TODO: add multi camera support
			if (cameraComponent.isActive)
			{
				auto viewport = renderer.getViewport();

				const auto ratio = viewport.GetAspectRatio();
				// TODO: Look into hardcoded values
				projectionComponent.projection.setProjection(
					-ratio, ratio,
					-1.0f, 1.0f,
					-1.0f, 1.0f
				);
				projectionComponent.projection.setPosition(transformComponent.position);
				projectionComponent.projection.setRotation(transformComponent.rotation.z);

				renderer.beginDraw(projectionComponent.projection.getViewProjectionMatrix());
			}
		}
	}

	void CameraSystem::render(World& world, graphics::Renderer2D& renderer, float alpha)
	{

	}
}
