#include "Scenes/Systems/RenderSystem.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/View.hpp"
#include "Scenes/Components/Renderable2DComponent.hpp"

namespace Cocoa::Scenes
{
	void RenderSystem::Update(World& world, float deltaTime)
	{

	}

	void RenderSystem::Render(World& world, Graphics::Renderer2D& renderer, float alpha)
	{
		View<Renderable2DComponent> view(world);
		for (auto [renderable] : view)
		{
			renderer.DrawQuad(renderable.Material);
		}
	}
}