#include "Scenes/Scene.hpp"
#include "Graphics/Renderer2D.hpp"

namespace Cocoa::Scenes
{
	// TODO: Viewport aspect ratio
	Scene::Scene() :
		m_camera(
			-800.f/600.0f, 800.f/600.0f,
			-1.0f, 1.0f,
			-1.0f, 1.0f),
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