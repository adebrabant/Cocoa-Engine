#pragma once

#include "Vector2f.hpp"

#include <array>
#include <cmath>
#include <cstddef>

namespace Cocoa::Math
{
    /// <summary>
    /// Represents a two-dimensional square matrix using single-precision floating-point values.
    /// </summary>
    /// <remarks>
    /// Matrix elements are stored in column-major order and operate on column vectors.
    /// </remarks>
    struct Matrix2f
    {
        /// <summary>
        /// Creates a zero-initialized matrix.
        /// </summary>
        constexpr Matrix2f() = default;

        /// <summary>
        /// Creates a matrix from values supplied column by column.
        /// </summary>
        /// <param name="m00">The first row value of the first column.</param>
        /// <param name="m10">The second row value of the first column.</param>
        /// <param name="m01">The first row value of the second column.</param>
        /// <param name="m11">The second row value of the second column.</param>
        constexpr Matrix2f(
            const float m00, const float m10,
            const float m01, const float m11)
        :
            m_elements{
                m00, m10,
                m01, m11
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
        [[nodiscard]] constexpr Matrix2f operator+(const Matrix2f& other) const
        {
            Matrix2f result;
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
        [[nodiscard]] constexpr Matrix2f operator-(const Matrix2f& other) const
        {
            Matrix2f result;
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
        [[nodiscard]] constexpr Matrix2f operator*(const float scalar) const
        {
            Matrix2f result;
            for (std::size_t i = 0; i < m_elements.size(); ++i)
            {
                result[i] = m_elements[i] * scalar;
            }

            return result;
        }

        /// <summary>
        /// Multiplies this matrix by another matrix.
        /// </summary>
        /// <param name="other">The matrix on the right side of the multiplication.</param>
        /// <returns>The resulting matrix product.</returns>
        [[nodiscard]] constexpr Matrix2f operator*(const Matrix2f& other) const
        {
            Matrix2f result;

            result[0] = (m_elements[0] * other[0]) + (m_elements[2] * other[1]);
            result[2] = (m_elements[0] * other[2]) + (m_elements[2] * other[3]);

            result[1] = (m_elements[1] * other[0]) + (m_elements[3] * other[1]);
            result[3] = (m_elements[1] * other[2]) + (m_elements[3] * other[3]);

            return result;
        }

        /// <summary>
        /// Transforms a two-dimensional column vector using this matrix.
        /// </summary>
        /// <param name="vector">The vector to transform.</param>
        /// <returns>The transformed vector.</returns>
        [[nodiscard]] constexpr Vector2f operator*(const Vector2f& vector) const
        {
            const float x = (m_elements[0] * vector.X) + (m_elements[2] * vector.Y);
            const float y = (m_elements[1] * vector.X) + (m_elements[3] * vector.Y);

            return Vector2f(x, y);
        }

        /// <summary>
        /// Creates an identity matrix.
        /// </summary>
        /// <returns>A matrix that leaves values unchanged when multiplied.</returns>
        [[nodiscard]] static constexpr Matrix2f Identity()
        {
            return Matrix2f(
                1.0f, 0.0f,
                0.0f, 1.0f
            );
        }

        /// <summary>
        /// Creates a two-dimensional scaling matrix.
        /// </summary>
        /// <param name="scale">The scale applied along the X and Y axes.</param>
        /// <returns>A matrix representing the requested scale.</returns>
        [[nodiscard]] static constexpr Matrix2f Scale(const Vector2f& scale)
        {
            return Matrix2f(
                scale.X, 0.0f,
                0.0f, scale.Y
            );
        }

        /// <summary>
        /// Creates a counterclockwise two-dimensional rotation matrix.
        /// </summary>
        /// <param name="angle">The rotation angle in radians.</param>
        /// <returns>A matrix representing the requested rotation.</returns>
        [[nodiscard]] static Matrix2f Rotation(const float angle)
        {
            const float cos = std::cos(angle);
            const float sin = std::sin(angle);

            return Matrix2f(
                cos, sin,
                -sin, cos
            );
        }

    private:
        std::array<float, 4> m_elements{};
    };
}