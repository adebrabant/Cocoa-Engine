#pragma once
#include "Graphics/GraphicsHandles.hpp"
#include "Graphics/SortLayer.hpp"
#include "Math/Vector2f.hpp"

namespace Cocoa::Scenes
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
