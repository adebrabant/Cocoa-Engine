#include "Core/Systems/CameraSystem.hpp"
#include "Core/ECS/World.hpp"
#include "Core/ECS/View.hpp"
#include "Core/Components/TransformComponent.hpp"
#include "Core/Components/CameraComponent.hpp"
#include "Graphics/IRenderer.hpp"

#include <iostream> 

namespace VexEngine::Core
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

	void CameraSystem::Render(World& world, Graphics::IRenderer& renderer, float alpha)
	{

	}
}