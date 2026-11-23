#pragma once

#include "Core/Color.hpp"
#include "Math/Vector2f.hpp"
#include "Graphics/SortLayer.hpp"
#include "Graphics/GraphicsHandles.hpp"

namespace Cocoa::Scenes
{
    struct LineComponent
    {
        Graphics::MaterialHandle Material{};
        Math::Vector2f StartPoint{-0.5f, 0.0f};
        Math::Vector2f EndPoint{0.5f, 0.0f};
        Core::Color Color{};
        float Thickness{0.05f};
        float Fade{0.02f};
        Graphics::SortLayer SortingLayer{Graphics::SortLayer::World};
        int SortingOrder{0};
    };
}