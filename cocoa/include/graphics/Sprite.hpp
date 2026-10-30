#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "math/Vector2f.hpp"

#include <string>

namespace cocoa::Graphics
{
    struct Sprite
    {
        std::string Id;
        TextureHandle Texture;
        Math::Vector2f MinUV;
        Math::Vector2f MaxUV;
    };
}