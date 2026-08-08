#pragma once

#include "Math/Matrix4f.hpp"
#include "Math/Vector3f.hpp"

namespace Cocoa::Graphics
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

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
        float m_rotation;
    };
}