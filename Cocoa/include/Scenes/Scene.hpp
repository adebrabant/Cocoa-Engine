#pragma once

#include "Graphics/OrthographicCamera.hpp"
#include "Scenes/ECS/World.hpp"

namespace Cocoa::Assets
{
	class ResourceLoader;
}

namespace Cocoa::Graphics
{
	class Renderer2D;
}

namespace Cocoa::Scenes
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
		Graphics::OrthographicCamera m_camera;
		World m_world;
	};
}