#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "graphics/SortLayer.hpp"
#include "math/Vector2f.hpp"

namespace cocoa::scenes
{
	struct SpriteComponent
	{
		graphics::MaterialHandle Material{};
		graphics::SpriteHandle Sprite{};
		math::Vector2f TilingFactor{1.0f, 1.0f};
		bool FlipVertical{false};
		bool FlipHorizontal{false};
		graphics::SortLayer SortingLayer{graphics::SortLayer::World};
		int SortingOrder{0};
	};
}
