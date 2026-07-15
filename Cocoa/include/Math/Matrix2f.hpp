#pragma once

#include <array>
#include <iostream>

#include "Vector2f.hpp"

namespace Cocoa::Math
{
    struct Matrix2f
    {
        constexpr Matrix2f() = default;

        constexpr Matrix2f(const float m00, const float m01, const float m10, const float m11) :
            m_elements{m00, m01, m10, m11} { }

       constexpr float& operator[](const std::size_t index)
        {
            return m_elements[index];
        }

        constexpr const float& operator[](const std::size_t index) const
        {
            return m_elements[index];
        }

        [[nodiscard]] constexpr Matrix2f operator+(const Matrix2f& other) const
        {
            Matrix2f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] + other[i];
            }

            return result;
        }

        [[nodiscard]] constexpr Matrix2f operator-(const Matrix2f& other) const
        {
            Matrix2f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] - other[i];
            }

            return result;
        }

        [[nodiscard]] constexpr Matrix2f operator*(const float scalar) const
        {
            Matrix2f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] * scalar;
            }

            return result;
        }

        [[nodiscard]] constexpr Matrix2f operator*(const Matrix2f& other) const
        {
            Matrix2f result;

            result[0] = (m_elements[0] * other[0]) + (m_elements[1] * other[2]);
            result[1] = (m_elements[0] * other[1]) + (m_elements[1] * other[3]);
            result[2] = (m_elements[2] * other[0]) + (m_elements[3] * other[2]);
            result[3] = (m_elements[2] * other[1]) + (m_elements[3] * other[3]);

            return result;
        }

        [[nodiscard]] constexpr Vector2f operator*(const Vector2f& vector) const
        {
            const float x = (m_elements[0] * vector.X) + (m_elements[1] * vector.Y);
            const float y = (m_elements[2] * vector.X) + (m_elements[3] * vector.Y);

            return Vector2f(x, y);
        }

        [[nodiscard]] static constexpr Matrix2f Identity()
        {
            return Matrix2f(1.0f, 0.0f, 0.0f, 1.0f);
        }

        [[nodiscard]] static constexpr Matrix2f Scale(const Vector2f& scale)
        {
            return Matrix2f(
                scale.X,
                0.0f,
                0.0f,
                scale.Y
            );
        }

        [[nodiscard]] static Matrix2f Rotation(const float angle)
        {
            const float cos = std::cos(angle);
            const float sin = std::sin(angle);
            return Matrix2f(
                cos,
                -sin,
                sin,
                cos
            );
        }

    private:
        std::array<float, 4> m_elements{};
    };
}
