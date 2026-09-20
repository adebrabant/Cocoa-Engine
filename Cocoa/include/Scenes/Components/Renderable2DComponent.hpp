#pragma once

#include "Graphics/GraphicsHandles.hpp"

namespace Cocoa::Scenes
{
	struct Renderable2DComponent
	{
		Graphics::MaterialHandle Material{};
		Graphics::SpriteHandle Sprite{};
		float TilingFactor{1.0f};
	};
}