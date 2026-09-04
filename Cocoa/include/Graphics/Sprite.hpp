#pragma once

#include "Graphics/GraphicsHandles.hpp"
#include "Math/Vector2f.hpp"

#include <string>

namespace Cocoa::Graphics
{
    struct Sprite
    {
        std::string Id;
        TextureHandle Texture;
        Math::Vector2f MinUV;
        Math::Vector2f MaxUV;
    };
}