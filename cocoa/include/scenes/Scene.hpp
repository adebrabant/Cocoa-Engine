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
		virtual void Load(assets::ResourceLoader& loader) = 0;
		virtual void Unload(assets::ResourceLoader& loader) = 0;
		virtual void Update(float deltaTime);
		virtual void Render(graphics::Renderer2D& renderer, float alpha);

	protected:
		World m_world;
	};
}
