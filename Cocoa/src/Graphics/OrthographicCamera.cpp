#include "Graphics/OrthographicCamera.hpp"

namespace Cocoa::Graphics
{
    OrthographicCamera::OrthographicCamera(
        const float left, const float right,
        const float bottom, const float top,
        const float near, const float far)
    :
        m_projectionMatrix(Math::Matrix4f::Ortho(left, right, bottom, top, near, far)),
        m_viewMatrix(Math::Matrix4f::Identity()),
        m_position(0.f, 0.0f, 0.0f),
        m_rotation(0.0f)
    {
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicCamera::SetProjection(
        const float left, const float right,
        const float bottom, const float top,
        const float near, const float far)
    {
        m_projectionMatrix = Math::Matrix4f::Ortho(left, right, bottom, top, near, far);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicCamera::SetPosition(const Math::Vector3f& position)
    {
        m_position = position;
        RecalculateViewProjectionMatrix();
    }

    void OrthographicCamera::SetRotation(const float rotation)
    {
        m_rotation = rotation;
        RecalculateViewProjectionMatrix();
    }

    void OrthographicCamera::RecalculateViewProjectionMatrix()
    {
        const Math::Matrix4f translation = Math::Matrix4f::Translation(m_position);
        const Math::Matrix4f rotation = Math::Matrix4f::RotationZ(m_rotation);
        const Math::Matrix4f transform = translation * rotation;

        m_viewMatrix = transform.Inverse();
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}
