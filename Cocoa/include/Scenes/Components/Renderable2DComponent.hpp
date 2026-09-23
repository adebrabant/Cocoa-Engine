#pragma once

#include "Math/Vector2f.hpp"
#include "Graphics/GraphicsHandles.hpp"

namespace Cocoa::Scenes
{
	struct Renderable2DComponent
	{
		Graphics::MaterialHandle Material{};
		Graphics::SpriteHandle Sprite{};
		Math::Vector2f TilingFactor{1.0f, 1.0f};
	};
}