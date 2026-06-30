#include "Systems/InputSystem.hpp"
#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/View.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Scenes/Components/VelocityComponent.hpp"	

namespace Sandbox::Systems
{
	InputSystem::InputSystem() :
		m_inputHandler()
	{

	}

	void InputSystem::Update(Cocoa::Scenes::World& world, float deltaTime)
	{
		Cocoa::Scenes::View<Cocoa::Scenes::VelocityComponent> view(world);
		for (auto [velocity] : view)
		{
			if (m_inputHandler.IsUpPressed())
			{
				velocity.DeltaY -= 0.5f * deltaTime;
			}
			if (m_inputHandler.IsDownPressed())
			{
				velocity.DeltaY += 0.5f * deltaTime;
			}

			if (m_inputHandler.IsRightPressed())
			{
				velocity.DeltaX += 0.5f * deltaTime;
			}
			
			if (m_inputHandler.IsLeftPressed())
			{
				velocity.DeltaX -= 0.5f * deltaTime;
			}

			velocity.DeltaX = 0.0f;
			velocity.DeltaY = 0.0f;
		}
	}

	void InputSystem::Render(Cocoa::Scenes::World& world, Cocoa::Graphics::Renderer2D& renderer, float alpha)
	{

	}
}