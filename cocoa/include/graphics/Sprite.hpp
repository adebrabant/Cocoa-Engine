#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "math/Vector2f.hpp"

#include <string>

namespace cocoa::graphics
{
    struct Sprite
    {
        std::string id;
        TextureHandle textureHandle;
        math::Vector2f minUV;
        math::Vector2f maxUV;
    };
}
