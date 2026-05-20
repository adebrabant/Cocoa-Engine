#pragma once

#include "Graphics/Renderer2D.hpp"

namespace VexEngine::Scenes
{
	class World;

	class ISystem
	{
	public:
		virtual ~ISystem() = default;
		virtual void Update(World& world, float deltaTime) = 0;
		virtual void Render(World& world, Graphics::Renderer2D& renderer, float alpha) = 0;
	};
}