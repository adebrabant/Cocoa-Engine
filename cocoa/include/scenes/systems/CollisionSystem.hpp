#pragma once

#include "scenes/systems/System.hpp"

namespace cocoa::scenes
{
	class World;

	class CollisionSystem : public System
	{
	public:
		CollisionSystem() = default;
		void Update(World& world, float deltaTime) override;
		void BeginRender(World& world, graphics::Renderer2D& renderer, float alpha) override;
		void Render(World& world, graphics::Renderer2D& renderer, float alpha) override;
	};
}
