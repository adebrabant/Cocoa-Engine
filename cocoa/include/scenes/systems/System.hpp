#pragma once

namespace cocoa::graphics
{
	class Renderer2D;
}

namespace cocoa::scenes
{
	class World;

	class System
	{
	public:
		virtual ~System() = default;
		virtual void Update(World& world, float deltaTime) = 0;
		virtual void BeginRender(World& world, graphics::Renderer2D& renderer, float alpha) = 0;
		virtual void Render(World& world, graphics::Renderer2D& renderer, float alpha) = 0;
	};
}
