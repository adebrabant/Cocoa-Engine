#pragma once

#include "Math/Vector2f.hpp"
#include "Graphics/GraphicsHandles.hpp"

namespace Cocoa::Scenes
{
	struct SpriteComponent
	{
		Graphics::MaterialHandle Material{};
		Graphics::SpriteHandle Sprite{};
		Math::Vector2f TilingFactor{1.0f, 1.0f};
		bool FlipVertical{false};
		bool FlipHorizontal{false};
	};
}