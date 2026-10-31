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

        void setProjection(float left, float right, float bottom, float top, float near, float far);
        [[nodiscard]] const math::Matrix4f& getProjectionMatrix() const { return m_projectionMatrix; }

        [[nodiscard]] const math::Matrix4f& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

        void setPosition(const math::Vector3f& position);
        [[nodiscard]] const math::Vector3f& getPosition() const { return m_position; }

        void setRotation(float rotation);
        [[nodiscard]] float getRotation() const { return m_rotation; }

    private:
        void recalculateViewProjectionMatrix();

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
