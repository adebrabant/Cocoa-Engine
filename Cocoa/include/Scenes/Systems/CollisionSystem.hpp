#pragma once

#include "Scenes/Systems/System.hpp"

namespace Cocoa::Scenes
{
	class World;

	class CollisionSystem : public System
	{
	public:
		CollisionSystem() = default;
		void Update(World& world, float deltaTime) override;
		void Render(World& world, Graphics::Renderer2D& renderer, float alpha) override;
	};
}