#pragma once

#include "scenes/systems/System.hpp"

namespace cocoa::scenes
{
	class Render2DSystem : public System
	{
	public:
		void Update(World& world, float deltaTime) override;
		void BeginRender(World& world, graphics::Renderer2D& renderer, float alpha) override;
		void Render(World& world, graphics::Renderer2D& renderer, float alpha) override;
	};
}
