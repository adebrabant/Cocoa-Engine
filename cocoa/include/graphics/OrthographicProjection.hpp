#pragma once

#include "math/Matrix4f.hpp"
#include "math/Vector2f.hpp"
#include "math/Vector3f.hpp"

namespace cocoa::graphics
{
    class OrthographicProjection
    {
    public:
        OrthographicProjection();
        OrthographicProjection(float left, float right, float bottom, float top, float near, float far);

        void SetProjection(float left, float right, float bottom, float top, float near, float far);
        [[nodiscard]] const math::Matrix4f& GetProjectionMatrix() const { return m_projectionMatrix; }

        [[nodiscard]] const math::Matrix4f& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

        void SetPosition(const math::Vector3f& position);
        [[nodiscard]] const math::Vector3f& GetPosition() const { return m_position; }

        void SetRotation(float rotation);
        [[nodiscard]] float GetRotation() const { return m_rotation; }

    private:
        void RecalculateViewProjectionMatrix();

    private:
        math::Matrix4f m_projectionMatrix;
        math::Matrix4f m_viewMatrix;
        math::Matrix4f m_viewProjectionMatrix;
        math::Vector3f m_position;
        math::Vector2f m_horizontalBounds;
        math::Vector2f m_verticalBounds;
        math::Vector2f m_depthBounds;
        float m_rotation;
    };
}
