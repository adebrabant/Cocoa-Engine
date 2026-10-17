#include "Scenes/Systems/CameraSystem.hpp"
#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/View.hpp"
#include "Scenes/Components/TransformComponent.hpp"
#include "Scenes/Components/CameraComponent.hpp"
#include "Scenes/Components/ProjectionComponent.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Graphics/OrthographicProjection.hpp"

namespace Cocoa::Scenes
{
	void CameraSystem::Update(World& world, float deltaTime)
	{

	}

	void CameraSystem::BeginRender(World& world, Graphics::Renderer2D& renderer, float alpha)
	{
		View<TransformComponent, CameraComponent, ProjectionComponent> view(world);

		for (auto [transformComponent, cameraComponent, projectionComponent] : view)
		{
			if (cameraComponent.IsActive)
			{
				auto viewport = renderer.GetViewport();

				const auto ratio = viewport.GetAspectRatio();
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