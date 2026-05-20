#pragma once

#include "Scenes/Systems/ISystem.hpp"
#include "Scenes/ECS/World.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Inputs/InputHandler.hpp"

namespace Vexxus::Systems
{
	class InputSystem : public VexEngine::Scenes::ISystem
	{
	public:
		InputSystem();
		~InputSystem() = default;
		void Update(VexEngine::Scenes::World& world, float deltaTime) override;
		void Render(VexEngine::Scenes::World& world, VexEngine::Graphics::Renderer2D& renderer, float alpha) override;

	private:
		VexEngine::Inputs::InputHandler m_inputHandler;
	};
}