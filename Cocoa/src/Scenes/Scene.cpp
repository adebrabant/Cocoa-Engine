#include "Scenes/Scene.hpp"
#include "Graphics/Renderer2D.hpp"

namespace Cocoa::Scenes
{
	Scene::Scene(const Graphics::Viewport& viewport) :
		m_camera(viewport),
		m_world()
	{

	}

	void Scene::Update(const float deltaTime)
	{
		m_world.Update(deltaTime);
	}

	void Scene::Render(Graphics::Renderer2D& renderer, const float alpha)
	{
		renderer.BeginDraw(m_camera.GetViewProjectionMatrix());
		m_world.Render(renderer, alpha);
		renderer.EndDraw();
	}
}