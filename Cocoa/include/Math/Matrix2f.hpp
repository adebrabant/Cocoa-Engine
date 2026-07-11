#pragma once

#include <array>

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

    private:
        std::array<float, 4> m_elements{};
    };
}