#include "scenes/Scene.hpp"
#include "graphics/Renderer2D.hpp"

namespace cocoa::scenes
{
	Scene::Scene() :
		m_world()
	{

	}

	void Scene::update(const float deltaTime)
	{
		m_world.update(deltaTime);
	}

	void Scene::render(graphics::Renderer2D& renderer, const float alpha)
	{
		m_world.beforeRender(renderer, alpha);
		m_world.render(renderer, alpha);
		renderer.endDraw();
	}
}
