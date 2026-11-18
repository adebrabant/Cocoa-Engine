#pragma once

#include "Core/Color.hpp"
#include "Graphics/SortLayer.hpp"
#include "Graphics/GraphicsHandles.hpp"

namespace Cocoa::Scenes
{
    struct CircleComponent
    {
        Graphics::MaterialHandle Material{};
        Core::Color Color{};
        float Thickness{0.5f};
        float Fade{0.02f};
        Graphics::SortLayer SortingLayer{Graphics::SortLayer::World};
        int SortingOrder{0};
    };
}