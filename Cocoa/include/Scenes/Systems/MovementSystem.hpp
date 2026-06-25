#pragma once

#include "Scenes/Systems/System.hpp"

namespace Cocoa::Scenes
{
	class MovementSystem : public System
	{
		void Update(World& world, float deltaTime) override;
		void Render(World& world, Graphics::Renderer2D& renderer, float alpha) override;
	};
}