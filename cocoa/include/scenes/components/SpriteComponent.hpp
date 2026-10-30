#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "graphics/SortLayer.hpp"
#include "math/Vector2f.hpp"

namespace cocoa::Scenes
{
	struct SpriteComponent
	{
		Graphics::MaterialHandle Material{};
		Graphics::SpriteHandle Sprite{};
		Math::Vector2f TilingFactor{1.0f, 1.0f};
		bool FlipVertical{false};
		bool FlipHorizontal{false};
		Graphics::SortLayer SortingLayer{Graphics::SortLayer::World};
		int SortingOrder{0};
	};
}