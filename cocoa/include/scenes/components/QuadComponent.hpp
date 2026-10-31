#pragma once
#include "graphics/GraphicsHandles.hpp"
#include "graphics/SortLayer.hpp"
#include "math/Vector2f.hpp"

namespace cocoa::scenes
{
    struct QuadComponent
    {
        graphics::MaterialHandle Material{};
        graphics::TextureHandle Texture{};
        math::Vector2f TilingFactor{1.0f, 1.0f};
        graphics::SortLayer SortingLayer{graphics::SortLayer::World};
        int SortingOrder{0};
    };
}
