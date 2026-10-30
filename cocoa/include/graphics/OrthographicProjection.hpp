#pragma once

#include "math/Matrix4f.hpp"
#include "math/Vector2f.hpp"
#include "math/Vector3f.hpp"

namespace cocoa::Graphics
{
    class OrthographicProjection
    {
    public:
        OrthographicProjection();
        OrthographicProjection(float left, float right, float bottom, float top, float near, float far);

        void SetProjection(float left, float right, float bottom, float top, float near, float far);
        [[nodiscard]] const Math::Matrix4f& GetProjectionMatrix() const { return m_projectionMatrix; }

        [[nodiscard]] const Math::Matrix4f& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

        void SetPosition(const Math::Vector3f& position);
        [[nodiscard]] const Math::Vector3f& GetPosition() const { return m_position; }

        void SetRotation(float rotation);
        [[nodiscard]] float GetRotation() const { return m_rotation; }

    private:
        void RecalculateViewProjectionMatrix();

    private:
        Math::Matrix4f m_projectionMatrix;
        Math::Matrix4f m_viewMatrix;
        Math::Matrix4f m_viewProjectionMatrix;
        Math::Vector3f m_position;
        Math::Vector2f m_horizontalBounds;
        Math::Vector2f m_verticalBounds;
        Math::Vector2f m_depthBounds;
        float m_rotation;
    };
}