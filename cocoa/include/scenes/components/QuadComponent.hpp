#pragma once
#include "graphics/GraphicsHandles.hpp"
#include "graphics/SortLayer.hpp"
#include "math/Vector2f.hpp"

namespace cocoa::Scenes
{
    struct QuadComponent
    {
        Graphics::MaterialHandle Material{};
        Graphics::TextureHandle Texture{};
        Math::Vector2f TilingFactor{1.0f, 1.0f};
        Graphics::SortLayer SortingLayer{Graphics::SortLayer::World};
        int SortingOrder{0};
    };
}
