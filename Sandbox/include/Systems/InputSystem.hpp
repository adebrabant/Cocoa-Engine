#pragma once

#include "Scenes/Systems/System.hpp"
#include "Inputs/InputHandler.hpp"

namespace Sandbox::Systems
{
	class InputSystem : public Cocoa::Scenes::System
	{
	public:
		InputSystem();
		~InputSystem() = default;
		void Update(Cocoa::Scenes::World& world, float deltaTime) override;
		void Render(Cocoa::Scenes::World& world, Cocoa::Graphics::Renderer2D& renderer, float alpha) override;

	private:
		Cocoa::Inputs::InputHandler m_inputHandler;
	};
}