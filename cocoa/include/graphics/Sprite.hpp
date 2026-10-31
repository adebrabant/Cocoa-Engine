#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "math/Vector2f.hpp"

#include <string>

namespace cocoa::graphics
{
    struct Sprite
    {
        std::string Id;
        TextureHandle Texture;
        math::Vector2f MinUV;
        math::Vector2f MaxUV;
    };
}
