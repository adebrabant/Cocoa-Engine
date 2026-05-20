#include "Scenes/Scene.hpp"
#include "Graphics/Renderer2D.hpp"

namespace VexEngine::Scenes
{
	Scene::Scene() :
		m_world()
	{

	}

	void Scene::Update(float deltaTime)
	{
		m_world.Update(deltaTime);
	}

	void Scene::Render(Graphics::Renderer2D& renderer, float alpha)
	{
		m_world.Render(renderer, alpha);
	}
}