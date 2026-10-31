#include "scenes/Scene.hpp"
#include "graphics/Renderer2D.hpp"

namespace cocoa::scenes
{
	Scene::Scene() :
		m_world()
	{

	}

	void Scene::Update(const float deltaTime)
	{
		m_world.Update(deltaTime);
	}

	void Scene::Render(graphics::Renderer2D& renderer, const float alpha)
	{
		m_world.BeforeRender(renderer, alpha);
		m_world.Render(renderer, alpha);
		renderer.EndDraw();
	}
}
