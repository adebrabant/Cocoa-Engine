#pragma once

#include "inputs/InputHandler.hpp"
#include "scenes/systems/System.hpp"

namespace sandbox
{
	class InputSystem : public cocoa::scenes::System
	{
	public:
		InputSystem();
		~InputSystem() override = default;
		void update(cocoa::scenes::World& world, float deltaTime) override;
		void render(cocoa::scenes::World& world, cocoa::graphics::Renderer2D& renderer, float alpha) override;

	private:
		cocoa::inputs::InputHandler m_inputHandler;
	};
}
