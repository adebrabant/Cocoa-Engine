#pragma once

#include "inputs/InputHandler.hpp"
#include "scenes/systems/System.hpp"

namespace Sandbox::Systems
{
	class InputSystem : public cocoa::Scenes::System
	{
	public:
		InputSystem();
		~InputSystem() override = default;
		void Update(cocoa::Scenes::World& world, float deltaTime) override;
		void Render(cocoa::Scenes::World& world, cocoa::Graphics::Renderer2D& renderer, float alpha) override;

	private:
		cocoa::Inputs::InputHandler m_inputHandler;
	};
}