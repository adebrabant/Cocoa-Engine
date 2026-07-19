#pragma once

#include "Math/Vector4f.hpp"
#include "Math/Vector3f.hpp"
#include "Math/Vector2f.hpp"

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

        /// <summary>
        /// Multiplies this matrix by another matrix.
        /// </summary>
        /// <param name="other">The matrix on the right side of the multiplication.</param>
        /// <returns>The resulting matrix product.</returns>
        [[nodiscard]] constexpr Matrix4f operator*(const Matrix4f& other) const
        {
            Matrix4f result;

            // top-left
            result[0] = (m_elements[0] * other[0]) + (m_elements[4] * other[1]) + (m_elements[8] * other[2]) + (m_elements[12] * other[3]);
            // upper-middle-left
            result[1] = (m_elements[1] * other[0]) + (m_elements[5] * other[1]) + (m_elements[9] * other[2]) + (m_elements[13] * other[3]);
            // lower-middle-left
            result[2] = (m_elements[2] * other[0]) + (m_elements[6] * other[1]) + (m_elements[10] * other[2]) + (m_elements[14] * other[3]);
            // bottom-left
            result[3] = (m_elements[3] * other[0]) + (m_elements[7] * other[1]) + (m_elements[11] * other[2]) + (m_elements[15] * other[3]);

            // top-center-left
            result[4] = (m_elements[0] * other[4]) + (m_elements[4] * other[5]) + (m_elements[8] * other[6]) + (m_elements[12] * other[7]);
            // upper-middle-center-left
            result[5] = (m_elements[1] * other[4]) + (m_elements[5] * other[5]) + (m_elements[9] * other[6]) + (m_elements[13] * other[7]);
            // lower-middle-center-left
            result[6] = (m_elements[2] * other[4]) + (m_elements[6] * other[5]) + (m_elements[10] * other[6]) + (m_elements[14] * other[7]);
            // bottom-center-left
            result[7] = (m_elements[3] * other[4]) + (m_elements[7] * other[5]) + (m_elements[11] * other[6]) + (m_elements[15] * other[7]);

            // top-center-right
            result[8] = (m_elements[0] * other[8]) + (m_elements[4] * other[9]) + (m_elements[8] * other[10]) + (m_elements[12] * other[11]);
            // upper-middle-center-right
            result[9] = (m_elements[1] * other[8]) + (m_elements[5] * other[9]) + (m_elements[9] * other[10]) + (m_elements[13] * other[11]);
            // lower-middle-center-right
            result[10] = (m_elements[2] * other[8]) + (m_elements[6] * other[9]) + (m_elements[10] * other[10]) + (m_elements[14] * other[11]);
            // bottom-center-right
            result[11] = (m_elements[3] * other[8]) + (m_elements[7] * other[9]) + (m_elements[11] * other[10]) + (m_elements[15] * other[11]);

            // top-right
            result[12] = (m_elements[0] * other[12]) + (m_elements[4] * other[13]) + (m_elements[8] * other[14]) + (m_elements[12] * other[15]);
            // upper-middle-right
            result[13] = (m_elements[1] * other[12]) + (m_elements[5] * other[13]) + (m_elements[9] * other[14]) + (m_elements[13] * other[15]);
            // lower-middle-right
            result[14] = (m_elements[2] * other[12]) + (m_elements[6] * other[13]) + (m_elements[10] * other[14]) + (m_elements[14] * other[15]);
            // bottom-right
            result[15] = (m_elements[3] * other[12]) + (m_elements[7] * other[13]) + (m_elements[11] * other[14]) + (m_elements[15] * other[15]);

            return result;
        }

        /// <summary>
        /// Transforms a four-dimensional column vector using this matrix.
        /// </summary>
        /// <param name="vector">The vector to transform.</param>
        /// <returns>The transformed vector.</returns>
        [[nodiscard]] constexpr Vector4f operator*(const Vector4f& vector) const
        {
            // X indexes times each vector component
            const float x = (m_elements[0] * vector.X) + (m_elements[4] * vector.Y) + (m_elements[8] * vector.Z) + (m_elements[12] * vector.W);
            // Y indexes times each vector component
            const float y = (m_elements[1] * vector.X) + (m_elements[5] * vector.Y) + (m_elements[9] * vector.Z) + (m_elements[13] * vector.W);
            // Z indexes times each vector component
            const float z = (m_elements[2] * vector.X) + (m_elements[6] * vector.Y) + (m_elements[10] * vector.Z) + (m_elements[14] * vector.W);
            // W indexes times each vector component
            const float w = (m_elements[3] * vector.X) + (m_elements[7] * vector.Y) + (m_elements[11] * vector.Z) + (m_elements[15] * vector.W);

            return Vector4f(x, y, z, w);
        }

        /// <summary>
        /// Creates an identity matrix.
        /// </summary>
        /// <returns>A matrix that leaves values unchanged when multiplied.</returns>
        [[nodiscard]] static constexpr Matrix4f Identity()
        {
            return Matrix4f(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        /// <summary>
        /// Creates a three-dimensional scaling matrix.
        /// </summary>
        /// <param name="scale">The scale applied along the X, Y, and Z axes.</param>
        /// <returns>A matrix representing the requested scale.</returns>
        [[nodiscard]] static constexpr Matrix4f Scale(const Vector3f& scale)
        {
            return Matrix4f(
                scale.X, 0.0f, 0.0f, 0.0f,
                0.0f, scale.Y, 0.0f, 0.0f,
                0.0f, 0.0f, scale.Z, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        /// <summary>
        /// Creates a two-dimensional scaling matrix using homogeneous coordinates.
        /// </summary>
        /// <param name="scale">The scale applied along the X and Y axes.</param>
        /// <returns>A matrix representing the requested scale.</returns>
        [[nodiscard]] static constexpr Matrix4f Scale(const Vector2f& scale)
        {
            return Matrix4f(
                scale.X, 0.0f, 0.0f, 0.0f,
                0.0f, scale.Y, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        /// <summary>
        /// Creates a counterclockwise rotation matrix around the X axis.
        /// </summary>
        /// <param name="angle">The rotation angle in radians.</param>
        /// <returns>A matrix representing the requested rotation.</returns>
        [[nodiscard]] static Matrix4f RotationX(const float angle)
        {
            const float cos = std::cos(angle);
            const float sin = std::sin(angle);
            return Matrix4f(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, cos, sin, 0.0f,
                0.0f, -sin, cos, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        /// <summary>
        /// Creates a counterclockwise rotation matrix around the Y axis.
        /// </summary>
        /// <param name="angle">The rotation angle in radians.</param>
        /// <returns>A matrix representing the requested rotation.</returns>
        [[nodiscard]] static Matrix4f RotationY(const float angle)
        {
            const float cos = std::cos(angle);
            const float sin = std::sin(angle);

            return Matrix4f(
                cos, 0.0f, -sin, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                sin, 0.0f, cos, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        /// <summary>
        /// Creates a counterclockwise rotation matrix around the Z axis.
        /// </summary>
        /// <param name="angle">The rotation angle in radians.</param>
        /// <returns>A matrix representing the requested rotation.</returns>
        [[nodiscard]] static Matrix4f RotationZ(const float angle)
        {
            const float cos = std::cos(angle);
            const float sin = std::sin(angle);

            return Matrix4f(
                cos, sin, 0.0f, 0.0f,
                -sin, cos, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        /// <summary>
        /// Creates a three-dimensional translation matrix using homogeneous coordinates.
        /// </summary>
        /// <param name="vector">The translation applied along the X, Y, and Z axes.</param>
        /// <returns>A matrix representing the requested translation.</returns>
        [[nodiscard]] static constexpr Matrix4f Translation(const Vector3f& vector)
        {
            return Matrix4f(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                vector.X, vector.Y, vector.Z, 1.0f
            );
        }

        /// <summary>
        /// Creates a two-dimensional translation matrix using homogeneous coordinates.
        /// </summary>
        /// <param name="vector">The translation applied along the X and Y axes.</param>
        /// <returns>A matrix representing the requested translation.</returns>
        [[nodiscard]] static constexpr Matrix4f Translation(const Vector2f& vector)
        {
            return Matrix4f(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                vector.X, vector.Y, 0.0f, 1.0f
            );
        }

    private:
        std::array<float, 16> m_elements{};
    };
}
