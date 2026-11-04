#pragma once

#include "Core/Color.hpp"
#include "Graphics/SortLayer.hpp"
#include "Graphics/GraphicsHandles.hpp"

namespace Cocoa::Scenes
{
    struct ColorQuadComponent
    {
        Graphics::MaterialHandle Material{};
        Core::Color Color{};
        Graphics::SortLayer SortingLayer{Graphics::SortLayer::World};
        int SortingOrder{0};
    };
}