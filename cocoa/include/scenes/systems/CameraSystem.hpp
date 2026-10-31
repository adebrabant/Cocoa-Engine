#pragma once

#include "scenes/systems/System.hpp"

namespace cocoa::scenes
{
	class World;

	class CameraSystem : public System
	{
	public:
		CameraSystem() = default;
		void update(World& world, float deltaTime) override;
		void beginRender(World& world, graphics::Renderer2D& renderer, float alpha) override;
		void render(World& world, graphics::Renderer2D& renderer, float alpha) override;
	};
}
