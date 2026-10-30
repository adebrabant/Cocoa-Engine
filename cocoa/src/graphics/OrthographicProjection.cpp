#include "graphics/OrthographicProjection.hpp"

namespace cocoa::Graphics
{
    OrthographicProjection::OrthographicProjection() :
        m_viewMatrix(Math::Matrix4f::Identity()),
        m_position(0.f, 0.0f, 0.0f),
        m_rotation(0.0f)
    {

    }

    OrthographicProjection::OrthographicProjection(
        const float left, const float right,
        const float bottom, const float top,
        const float near, const float far)
    :
        m_projectionMatrix(Math::Matrix4f::Ortho(left, right, bottom, top, near, far)),
        m_viewMatrix(Math::Matrix4f::Identity()),
        m_position(0.f, 0.0f, 0.0f),
        m_horizontalBounds(left, right),
        m_verticalBounds(bottom, top),
        m_depthBounds(near, far),
        m_rotation(0.0f)
    {
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicProjection::SetProjection(
        const float left, const float right,
        const float bottom, const float top,
        const float near, const float far)
    {
        if (m_horizontalBounds.X == left && m_horizontalBounds.Y == right &&
            m_verticalBounds.X == bottom && m_verticalBounds.Y == top &&
            m_depthBounds.X == near && m_depthBounds.Y == far) return;

        m_projectionMatrix = Math::Matrix4f::Ortho(left, right, bottom, top, near, far);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;

        m_horizontalBounds.X = left;
        m_horizontalBounds.Y = right;

        m_verticalBounds.X = bottom;
        m_verticalBounds.Y = top;

        m_depthBounds.X = near;
        m_depthBounds.Y = far;
    }

    void OrthographicProjection::SetPosition(const Math::Vector3f& position)
    {
        if (m_position == position)
            return;

        m_position = position;
        RecalculateViewProjectionMatrix();
    }

    void OrthographicProjection::SetRotation(const float rotation)
    {
        if (m_rotation == rotation)
            return;

        m_rotation = rotation;
        RecalculateViewProjectionMatrix();
    }

    void OrthographicProjection::RecalculateViewProjectionMatrix()
    {
        const Math::Matrix4f translation = Math::Matrix4f::Translation(m_position);
        const Math::Matrix4f rotation = Math::Matrix4f::RotationZ(m_rotation);
        const Math::Matrix4f transform = translation * rotation;

        m_viewMatrix = transform.Inverse();
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}
