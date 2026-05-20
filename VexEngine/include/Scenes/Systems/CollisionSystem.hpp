#pragma once

#include "Scenes/Systems/ISystem.hpp"
#include <Graphics/Renderer2D.hpp>

namespace VexEngine::Scenes
{
	class World;

	class CollisionSystem : public ISystem
	{
	public:
		CollisionSystem() = default;
		void Update(World& world, float deltaTime) override;
		void Render(World& world, Graphics::Renderer2D& renderer, float alpha) override;
	};
}