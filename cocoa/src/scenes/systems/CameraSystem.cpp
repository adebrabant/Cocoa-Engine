#include "scenes/systems/CameraSystem.hpp"
#include "graphics/OrthographicProjection.hpp"
#include "graphics/Renderer2D.hpp"
#include "scenes/components/CameraComponent.hpp"
#include "scenes/components/ProjectionComponent.hpp"
#include "scenes/components/TransformComponent.hpp"
#include "scenes/ecs/View.hpp"
#include "scenes/ecs/World.hpp"

namespace cocoa::Scenes
{
	void CameraSystem::Update(World& world, float deltaTime)
	{

	}

	// TODO: Look into fallback or required components if not found
	void CameraSystem::BeginRender(World& world, Graphics::Renderer2D& renderer, float alpha)
	{
		View<TransformComponent, CameraComponent, ProjectionComponent> view(world);

		for (auto [transformComponent, cameraComponent, projectionComponent] : view)
		{
			// TODO: Add multi camera support
			if (cameraComponent.IsActive)
			{
				auto viewport = renderer.GetViewport();

				const auto ratio = viewport.GetAspectRatio();
				// TODO: Look into hardcoded values
				projectionComponent.Projection.SetProjection(
					-ratio, ratio,
					-1.0f, 1.0f,
					-1.0f, 1.0f
				);
				projectionComponent.Projection.SetPosition(transformComponent.Position);
				projectionComponent.Projection.SetRotation(transformComponent.Rotation.Z);

				renderer.BeginDraw(projectionComponent.Projection.GetViewProjectionMatrix());
			}
		}
	}

	void CameraSystem::Render(World& world, Graphics::Renderer2D& renderer, float alpha)
	{

	}
}
