#pragma once

#include "Vector3f.hpp"
#include "Vector2f.hpp"
#include <cstddef>
#include <array>
#include <cmath>

namespace Cocoa::Math
{
    /// <summary>
    /// Represents a three-dimensional square matrix using single-precision floating-point values.
    /// </summary>
    /// <remarks>
    /// Matrix elements are stored in column-major order and operate on column vectors.
    /// </remarks>
    struct Matrix3f
    {
        constexpr Matrix3f() = default;

        /// <summary>
        /// Creates a matrix from values supplied column by column.
        /// </summary>
        /// <param name="m00">The first row value of the first column.</param>
        /// <param name="m10">The second row value of the first column.</param>
        /// <param name="m20">The third row value of the first column.</param>
        /// <param name="m01">The first row value of the second column.</param>
        /// <param name="m11">The second row value of the second column.</param>
        /// <param name="m21">The third row value of the second column.</param>
        /// <param name="m02">The first row value of the third column.</param>
        /// <param name="m12">The second row value of the third column.</param>
        /// <param name="m22">The third row value of the third column.</param>
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
        [[nodiscard]] constexpr Matrix3f operator+(const Matrix3f& other) const
        {
            Matrix3f result;
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
        [[nodiscard]] constexpr Matrix3f operator-(const Matrix3f& other) const
        {
            Matrix3f result;
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
        [[nodiscard]] constexpr Matrix3f operator*(const float scalar) const
        {
            Matrix3f result;
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

        /// <summary>
        /// Transforms a three-dimensional column vector using this matrix.
        /// </summary>
        /// <param name="vector">The vector to transform.</param>
        /// <returns>The transformed vector.</returns>
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

        /// <summary>
        /// Creates an identity matrix.
        /// </summary>
        /// <returns>A matrix that leaves values unchanged when multiplied.</returns>
        [[nodiscard]] static constexpr Matrix3f Identity()
        {
            return Matrix3f(
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }

        /// <summary>
        /// Creates a three-dimensional scaling matrix.
        /// </summary>
        /// <param name="scale">The scale applied along the X, Y, and Z axes.</param>
        /// <returns>A matrix representing the requested scale.</returns>
        [[nodiscard]] static constexpr Matrix3f Scale(const Vector3f& scale)
        {
            return Matrix3f(
                scale.X, 0.0f, 0.0f,
                0.0f, scale.Y, 0.0f,
                0.0f, 0.0f, scale.Z
            );
        }

        /// <summary>
        /// Creates a two-dimensional scaling matrix using homogeneous coordinates.
        /// </summary>
        /// <param name="scale">The scale applied along the X and Y axes.</param>
        /// <returns>A matrix representing the requested scale.</returns>
        [[nodiscard]] static constexpr Matrix3f Scale(const Vector2f& scale)
        {
            return Matrix3f(
                scale.X, 0.0f, 0.0f,
                0.0f, scale.Y, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }

        /// <summary>
        /// Creates a counterclockwise rotation matrix around the X axis.
        /// </summary>
        /// <param name="angle">The rotation angle in radians.</param>
        /// <returns>A matrix representing the requested rotation.</returns>
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

        /// <summary>
        /// Creates a counterclockwise rotation matrix around the Y axis.
        /// </summary>
        /// <param name="angle">The rotation angle in radians.</param>
        /// <returns>A matrix representing the requested rotation.</returns>
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

        /// <summary>
        /// Creates a counterclockwise rotation matrix around the Z axis.
        /// </summary>
        /// <param name="angle">The rotation angle in radians.</param>
        /// <returns>A matrix representing the requested rotation.</returns>
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

        /// <summary>
        /// Creates a two-dimensional translation matrix using homogeneous coordinates.
        /// </summary>
        /// <param name="vector">The translation applied along the X and Y axes.</param>
        /// <returns>A matrix representing the requested translation.</returns>
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
