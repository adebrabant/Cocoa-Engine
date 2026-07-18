#pragma once

#include "Vector3f.hpp"
#include <cstddef>
#include <array>
#include <cmath>

#include "Vector2f.hpp"

namespace Cocoa::Math
{
    struct Matrix3f
    {
        constexpr Matrix3f() = default;

        constexpr Matrix3f(
            const float m00, const float m10, const float m20, // Vector 1
            const float m01, const float m11, const float m21, // Vector 2
            const float m02, const float m12, const float m22) // Vector 3
        :
            m_elements{
                m00, m10, m20,
                m01, m11, m21,
                m02, m12, m22
            }
        {

        }

        constexpr float& operator[](const std::size_t index)
        {
            return m_elements[index];
        }

        constexpr const float& operator[](const std::size_t index) const
        {
            return m_elements[index];
        }

        [[nodiscard]] constexpr Matrix3f operator+(const Matrix3f& other) const
        {
            Matrix3f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] + other[i];
            }

            return result;
        }

        [[nodiscard]] constexpr Matrix3f operator-(const Matrix3f& other) const
        {
            Matrix3f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] - other[i];
            }

            return result;
        }

        [[nodiscard]] constexpr Matrix3f operator*(const float scalar) const
        {
            Matrix3f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] * scalar;
            }

            return result;
        }

        [[nodiscard]] constexpr Matrix3f operator*(const Matrix3f& other) const
        {
            Matrix3f result;

            // top-left
            result[0] = (m_elements[0] * other[0]) + (m_elements[3] * other[1]) + (m_elements[6] * other[2]);
            // middle-left
            result[1] = (m_elements[1] * other[0]) + (m_elements[4] * other[1]) + (m_elements[7] * other[2]);
            // bottom-left
            result[2] = (m_elements[2] * other[0]) + (m_elements[5] * other[1]) + (m_elements[8] * other[2]);

            // top-middle
            result[3] = (m_elements[0] * other[3]) + (m_elements[3] * other[4]) + (m_elements[6] * other[5]);
            // center
            result[4] = (m_elements[1] * other[3]) + (m_elements[4] * other[4]) + (m_elements[7] * other[5]);
            // bottom-middle
            result[5] = (m_elements[2] * other[3]) + (m_elements[5] * other[4]) + (m_elements[8] * other[5]);

            // top-right
            result[6] = (m_elements[0] * other[6]) + (m_elements[3] * other[7]) + (m_elements[6] * other[8]);
            // middle-right
            result[7] = (m_elements[1] * other[6]) + (m_elements[4] * other[7]) + (m_elements[7] * other[8]);
            // bottom-right
            result[8] = (m_elements[2] * other[6]) + (m_elements[5] * other[7]) + (m_elements[8] * other[8]);

            return result;
        }

        [[nodiscard]] constexpr Vector3f operator*(const Vector3f& vector) const
        {
            // X indexes times each vector component
            const float x = (m_elements[0] * vector.X) + (m_elements[3] * vector.Y) + (m_elements[6] * vector.Z);
            // Y indexes times each vector component
            const float y = (m_elements[1] * vector.X) + (m_elements[4] * vector.Y) + (m_elements[7] * vector.Z);
            // Z indexes times each vector component
            const float z = (m_elements[2] * vector.X) + (m_elements[5] * vector.Y) + (m_elements[8] * vector.Z);

            return Vector3f(x, y, z);
        }

        [[nodiscard]] static constexpr Matrix3f Identity()
        {
            return Matrix3f(
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }

        [[nodiscard]] static constexpr Matrix3f Scale(const Vector3f& scale)
        {
            return Matrix3f(
                scale.X, 0.0f, 0.0f,
                0.0f, scale.Y, 0.0f,
                0.0f, 0.0f, scale.Z
            );
        }

        [[nodiscard]] static constexpr Matrix3f Scale(const Vector2f& scale)
        {
            return Matrix3f(
                scale.X, 0.0f, 0.0f,
                0.0f, scale.Y, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }

        [[nodiscard]] static Matrix3f RotationX(const float angle)
        {
            const float cos = std::cos(angle);
            const float sin = std::sin(angle);
            return Matrix3f(
                1.0f, 0.0f, 0.0f,
                0.0f, cos, sin,
                0.0f, -sin, cos
            );
        }

        [[nodiscard]] static Matrix3f RotationY(const float angle)
        {
            const float cos = std::cos(angle);
            const float sin = std::sin(angle);
            return Matrix3f(
                cos, 0.0f, -sin,
                0.0f, 1.0f, 0.0f,
                sin, 0.0f, cos
            );
        }

        [[nodiscard]] static Matrix3f RotationZ(const float angle)
        {
            const float cos = std::cos(angle);
            const float sin = std::sin(angle);
            return Matrix3f(
                cos, sin, 0.0f,
                -sin, cos, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }

        [[nodiscard]] static constexpr Matrix3f Translation(const Vector2f vector)
        {
            return Matrix3f(
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                vector.X, vector.Y, 1.0f
            );
        }

    private:
        std::array<float, 9> m_elements{};
    };
}
