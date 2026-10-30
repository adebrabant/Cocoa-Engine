#pragma once

#include "scenes/systems/System.hpp"

namespace cocoa::Scenes
{
	class Render2DSystem : public System
	{
	public:
		void Update(World& world, float deltaTime) override;
		void BeginRender(World& world, Graphics::Renderer2D& renderer, float alpha) override;
		void Render(World& world, Graphics::Renderer2D& renderer, float alpha) override;
	};
}