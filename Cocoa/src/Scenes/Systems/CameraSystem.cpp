#include "Scenes/Systems/CameraSystem.hpp"
#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/View.hpp"
#include "Scenes/Components/TransformComponent.hpp"
#include "Scenes/Components/CameraComponent.hpp"
#include "Graphics/Renderer2D.hpp"

#include <iostream> 

namespace Cocoa::Scenes
{
	void CameraSystem::Update(World& world, float deltaTime)
	{
		View<TransformComponent, CameraComponent> view(world);

		for (auto [transform, camera] : view)
		{

		}
	}

	void CameraSystem::Render(World& world, Graphics::Renderer2D& renderer, float alpha)
	{

	}
}