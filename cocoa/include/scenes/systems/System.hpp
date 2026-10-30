#pragma once

namespace cocoa::Graphics
{
	class Renderer2D;
}

namespace cocoa::Scenes
{
	class World;

	class System
	{
	public:
		virtual ~System() = default;
		virtual void Update(World& world, float deltaTime) = 0;
		virtual void BeginRender(World& world, Graphics::Renderer2D& renderer, float alpha) = 0;
		virtual void Render(World& world, Graphics::Renderer2D& renderer, float alpha) = 0;
	};
}