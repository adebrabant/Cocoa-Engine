#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "graphics/SortLayer.hpp"
#include "math/Vector2f.hpp"

namespace cocoa::scenes
{
	struct SpriteComponent
	{
		graphics::MaterialHandle materialHandle{};
		graphics::SpriteHandle spriteHandle{};
		math::Vector2f tilingFactor{1.0f, 1.0f};
		bool flipVertical{false};
		bool flipHorizontal{false};
		graphics::SortLayer sortingLayer{graphics::SortLayer::World};
		int sortingOrder{0};
	};
}
