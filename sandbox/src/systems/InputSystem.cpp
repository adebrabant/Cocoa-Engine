#include "systems/InputSystem.hpp"
#include "graphics/Renderer2D.hpp"
#include "scenes/components/VelocityComponent.hpp"
#include "scenes/ecs/View.hpp"
#include "scenes/ecs/World.hpp"

namespace sandbox
{
	InputSystem::InputSystem() :
		m_inputHandler()
	{

	}

	void InputSystem::Update(cocoa::scenes::World& world, float deltaTime)
	{
		cocoa::scenes::View<cocoa::scenes::VelocityComponent> view(world);
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

	void InputSystem::Render(cocoa::scenes::World& world, cocoa::graphics::Renderer2D& renderer, float alpha)
	{

	}
}
