#pragma once

#include "scenes/ecs/World.hpp"

namespace cocoa::assets
{
	class ResourceLoader;
}

namespace cocoa::graphics
{
	class Renderer2D;
}

namespace cocoa::scenes
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;
		virtual void load(assets::ResourceLoader& loader) = 0;
		virtual void unload(assets::ResourceLoader& loader) = 0;
		virtual void update(float deltaTime);
		virtual void render(graphics::Renderer2D& renderer, float alpha);

	protected:
		World m_world;
	};
}
