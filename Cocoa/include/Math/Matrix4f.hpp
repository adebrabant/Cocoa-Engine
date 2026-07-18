#pragma once

#include "Vector3f.hpp"
#include <cstddef>
#include <array>
#include <cmath>

namespace Cocoa::Math
{
    /// <summary>
    /// Represents a four-dimensional square matrix using single-precision floating-point values.
    /// </summary>
    /// <remarks>
    /// Matrix elements are stored in column-major order and operate on column vectors.
    /// </remarks>
    struct Matrix4f
    {
        constexpr Matrix4f() = default;

        /// <summary>
        /// Creates a matrix from values supplied column by column.
        /// </summary>
        /// <param name="m00">The first row value of the first column.</param>
        /// <param name="m10">The second row value of the first column.</param>
        /// <param name="m20">The third row value of the first column.</param>
        /// <param name="m30">The fourth row value of the first column.</param>
        /// <param name="m01">The first row value of the second column.</param>
        /// <param name="m11">The second row value of the second column.</param>
        /// <param name="m21">The third row value of the second column.</param>
        /// <param name="m31">The fourth row value of the second column.</param>
        /// <param name="m02">The first row value of the third column.</param>
        /// <param name="m12">The second row value of the third column.</param>
        /// <param name="m22">The third row value of the third column.</param>
        /// <param name="m32">The fourth row value of the third column.</param>
        /// <param name="m03">The first row value of the fourth column.</param>
        /// <param name="m13">The second row value of the fourth column.</param>
        /// <param name="m23">The third row value of the fourth column.</param>
        /// <param name="m33">The fourth row value of the fourth column.</param>
        constexpr Matrix4f(
            const float m00, const float m10, const float m20, const float m30,
            const float m01, const float m11, const float m21, const float m31,
            const float m02, const float m12, const float m22, const float m32,
            const float m03, const float m13, const float m23, const float m33)
        :
            m_elements{
                m00, m10, m20, m30,
                m01, m11, m21, m31,
                m02, m12, m22, m32,
                m03, m13, m23, m33,
            }
        {

        }

        /// <summary>
        /// Returns a mutable reference to the element at the specified column-major index.
        /// </summary>
        /// <param name="index">The zero-based element index.</param>
        /// <returns>A mutable reference to the matrix element.</returns>
        constexpr float& operator[](const std::size_t index)
        {
            return m_elements[index];
        }

        /// <summary>
        /// Returns a constant reference to the element at the specified column-major index.
        /// </summary>
        /// <param name="index">The zero-based element index.</param>
        /// <returns>A constant reference to the matrix element.</returns>
        constexpr const float& operator[](const std::size_t index) const
        {
            return m_elements[index];
        }

        /// <summary>
        /// Adds another matrix to this matrix.
        /// </summary>
        /// <param name="other">The matrix to add.</param>
        /// <returns>A matrix containing the element-wise sum.</returns>
        [[nodiscard]] constexpr Matrix4f operator+(const Matrix4f& other) const
        {
            Matrix4f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] + other[i];
            }

            return result;
        }

        /// <summary>
        /// Subtracts another matrix from this matrix.
        /// </summary>
        /// <param name="other">The matrix to subtract.</param>
        /// <returns>A matrix containing the element-wise difference.</returns>
        [[nodiscard]] constexpr Matrix4f operator-(const Matrix4f& other) const
        {
            Matrix4f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] - other[i];
            }

            return result;
        }

        /// <summary>
        /// Multiplies every matrix element by a scalar value.
        /// </summary>
        /// <param name="scalar">The scalar multiplier.</param>
        /// <returns>The scaled matrix.</returns>
        [[nodiscard]] constexpr Matrix4f operator*(const float scalar) const
        {
            Matrix4f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] * scalar;
            }

            return result;
        }

    private:
        std::array<float, 16> m_elements{};
    };
}
