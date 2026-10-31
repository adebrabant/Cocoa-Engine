#pragma once
#include "graphics/GraphicsHandles.hpp"
#include "graphics/SortLayer.hpp"
#include "math/Vector2f.hpp"

namespace cocoa::scenes
{
    struct QuadComponent
    {
        graphics::MaterialHandle materialHandle{};
        graphics::TextureHandle textureHandle{};
        math::Vector2f tilingFactor{1.0f, 1.0f};
        graphics::SortLayer sortingLayer{graphics::SortLayer::World};
        int sortingOrder{0};
    };
}
