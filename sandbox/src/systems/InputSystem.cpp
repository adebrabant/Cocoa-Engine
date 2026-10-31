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

	void InputSystem::update(cocoa::scenes::World& world, float deltaTime)
	{
		cocoa::scenes::View<cocoa::scenes::VelocityComponent> view(world);
		for (auto [velocity] : view)
		{
			if (m_inputHandler.isUpPressed())
			{
				velocity.deltaY -= 0.5f * deltaTime;
			}
			if (m_inputHandler.isDownPressed())
			{
				velocity.deltaY += 0.5f * deltaTime;
			}

			if (m_inputHandler.isRightPressed())
			{
				velocity.deltaX += 0.5f * deltaTime;
			}

			if (m_inputHandler.isLeftPressed())
			{
				velocity.deltaX -= 0.5f * deltaTime;
			}

			velocity.deltaX = 0.0f;
			velocity.deltaY = 0.0f;
		}
	}

	void InputSystem::render(cocoa::scenes::World& world, cocoa::graphics::Renderer2D& renderer, float alpha)
	{

	}
}
