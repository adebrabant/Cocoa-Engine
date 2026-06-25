#pragma once

namespace Cocoa::Graphics
{
	class Renderer2D;
}

namespace Cocoa::Scenes
{
	class World;

	class System
	{
	public:
		virtual ~System() = default;
		virtual void Update(World& world, float deltaTime) = 0;
		virtual void Render(World& world, Graphics::Renderer2D& renderer, float alpha) = 0;
	};
}