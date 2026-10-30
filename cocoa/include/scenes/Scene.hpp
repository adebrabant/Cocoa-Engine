#pragma once

#include "scenes/ecs/World.hpp"

namespace cocoa::Assets
{
	class ResourceLoader;
}

namespace cocoa::Graphics
{
	class Renderer2D;
}

namespace cocoa::Scenes
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;
		virtual void Load(Assets::ResourceLoader& loader) = 0;
		virtual void Unload(Assets::ResourceLoader& loader) = 0;
		virtual void Update(float deltaTime);
		virtual void Render(Graphics::Renderer2D& renderer, float alpha);

	protected:
		World m_world;
	};
}