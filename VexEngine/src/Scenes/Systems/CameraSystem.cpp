#include "Scenes/Systems/CameraSystem.hpp"
#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/View.hpp"
#include "Scenes/Components/TransformComponent.hpp"
#include "Scenes/Components/CameraComponent.hpp"
#include "Graphics/Renderer2D.hpp"

#include <iostream> 

namespace VexEngine::Scenes
{
	void CameraSystem::Update(World& world, float deltaTime)
	{
		View<TransformComponent, CameraComponent> view(world);

		for (auto [transform, camera] : view)
		{
			transform.X += 1.0f * deltaTime;
			transform.Y += 0.0f;
			transform.Z += 0.5f * deltaTime;

			//std::cout << "Camera Position -> X: "
			//	<< transform.X
			//	<< ", Y: "
			//	<< transform.Y
			//	<< ", Z: "
			//	<< transform.Z
			//	<< std::endl;
		}
	}

	void CameraSystem::Render(World& world, Graphics::Renderer2D& renderer, float alpha)
	{

	}
}