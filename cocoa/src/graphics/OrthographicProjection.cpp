#include "graphics/OrthographicProjection.hpp"

namespace cocoa::graphics
{
    OrthographicProjection::OrthographicProjection() :
        m_viewMatrix(math::Matrix4f::identity()),
        m_position(0.f, 0.0f, 0.0f),
        m_rotation(0.0f)
    {

    }

    OrthographicProjection::OrthographicProjection(
        const float left, const float right,
        const float bottom, const float top,
        const float near, const float far)
    :
        m_projectionMatrix(math::Matrix4f::ortho(left, right, bottom, top, near, far)),
        m_viewMatrix(math::Matrix4f::identity()),
        m_position(0.f, 0.0f, 0.0f),
        m_horizontalBounds(left, right),
        m_verticalBounds(bottom, top),
        m_depthBounds(near, far),
        m_rotation(0.0f)
    {
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicProjection::setProjection(
        const float left, const float right,
        const float bottom, const float top,
        const float near, const float far)
    {
        if (m_horizontalBounds.x == left && m_horizontalBounds.y == right &&
            m_verticalBounds.x == bottom && m_verticalBounds.y == top &&
            m_depthBounds.x == near && m_depthBounds.y == far) return;

        m_projectionMatrix = math::Matrix4f::ortho(left, right, bottom, top, near, far);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;

        m_horizontalBounds.x = left;
        m_horizontalBounds.y = right;

        m_verticalBounds.x = bottom;
        m_verticalBounds.y = top;

        m_depthBounds.x = near;
        m_depthBounds.y = far;
    }

    void OrthographicProjection::setPosition(const math::Vector3f& position)
    {
        if (m_position == position)
            return;

        m_position = position;
        recalculateViewProjectionMatrix();
    }

    void OrthographicProjection::setRotation(const float rotation)
    {
        if (m_rotation == rotation)
            return;

        m_rotation = rotation;
        recalculateViewProjectionMatrix();
    }

    void OrthographicProjection::recalculateViewProjectionMatrix()
    {
        const math::Matrix4f translation = math::Matrix4f::translation(m_position);
        const math::Matrix4f rotation = math::Matrix4f::rotationZ(m_rotation);
        const math::Matrix4f transform = translation * rotation;

        m_viewMatrix = transform.inverse();
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}
