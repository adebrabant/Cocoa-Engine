#pragma once

#include "Scenes/Systems/ISystem.hpp"
#include "Scenes/ECS/World.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Inputs/InputHandler.hpp"

namespace Vexxus::Systems
{
	class InputSystem : public Cocoa::Scenes::ISystem
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