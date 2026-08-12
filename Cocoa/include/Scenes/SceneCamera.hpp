#pragma once

#include <cstdint>

#include "Graphics/OrthographicCamera.hpp"

namespace Cocoa::Graphics
{
    struct Viewport;
}

namespace Cocoa::Math
{
    struct Matrix4f;
}

namespace Cocoa::Scenes
{
    class SceneCamera
    {
    public:
        explicit SceneCamera(const Graphics::Viewport& viewport);
        ~SceneCamera() = default;

        [[nodiscard]] Math::Matrix4f GetViewProjectionMatrix();

    private:
        void SyncProjection();

    private:
        const Graphics::Viewport& m_viewport;
        Graphics::OrthographicCamera m_orthoCamera;
        uint32_t m_cachedWidth;
        uint32_t m_cachedHeight;
    };
}