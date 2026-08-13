#include "Scenes/SceneCamera.hpp"
#include "Graphics/Viewport.hpp"
#include "Math/Matrix4f.hpp"

namespace Cocoa::Scenes
{
    SceneCamera::SceneCamera(const Graphics::Viewport& viewport) :
        m_viewport(viewport),
        m_orthoCamera(
            -viewport.GetAspectRatio(),
            viewport.GetAspectRatio(),
            -1.0f, 1.0f,
            -1.0f, 1.0f),
        m_cachedWidth(viewport.Width),
        m_cachedHeight(viewport.Height)
    {

    }

    const Math::Matrix4f& SceneCamera::GetViewProjectionMatrix()
    {
        SyncProjection();
        return m_orthoCamera.GetViewProjectionMatrix();
    }

    void SceneCamera::SyncProjection()
    {
        if (m_viewport.Height == m_cachedHeight &&
            m_viewport.Width == m_cachedWidth)
            return;

        m_cachedWidth = m_viewport.Width;
        m_cachedHeight = m_viewport.Height;
        const auto ratio = m_viewport.GetAspectRatio();
        m_orthoCamera.SetProjection(
            -ratio, ratio,
            -1.0f, 1.0f,
            -1.0f, 1.0f
        );
    }
}
