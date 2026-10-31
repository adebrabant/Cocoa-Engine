#pragma once

#include <cassert>
#include <cmath>

namespace cocoa::math
{
    /// <summary>
    /// Represents a four-dimensional vector using single-precision floating-point components.
    /// </summary>
    struct Vector4f
    {
        float x{0.0f};
        float y{0.0f};
        float z{0.0f};
        float w{0.0f};

        constexpr Vector4f() = default;

        constexpr Vector4f(const float x, const float y, const float z, const float w) :
            x(x), y(y), z(z), w(w)
        {

        }

    	/// <summary>
		/// Adds another vector to this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A new vector containing the component-wise sum.</returns>
		[[nodiscard]] constexpr Vector4f operator+(const Vector4f& other) const
		{
			const auto xSum = x + other.x;
			const auto ySum = y + other.y;
			const auto zSum = z + other.z;
        	const auto wSum = w + other.w;

			return Vector4f(xSum, ySum, zSum, wSum);
		}

		/// <summary>
		/// Adds another vector to this vector.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A reference to this vector after the addition.</returns>
		constexpr Vector4f& operator+=(const Vector4f& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
        	w += other.w;

			return *this;
		}

		/// <summary>
		/// Subtracts another vector from this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A new vector containing the component-wise difference.</returns>
		[[nodiscard]] constexpr Vector4f operator-(const Vector4f& other) const
		{
			const auto xDifference = x - other.x;
			const auto yDifference = y - other.y;
			const auto zDifference = z - other.z;
        	const auto wDifference = w - other.w;

			return Vector4f(xDifference, yDifference, zDifference, wDifference);
		}

		/// <summary>
		/// Subtracts another vector from this vector.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A reference to this vector after the subtraction.</returns>
		constexpr Vector4f& operator-=(const Vector4f& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
        	w -= other.w;

			return *this;
		}

		/// <summary>
		/// Multiplies this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A new vector scaled by the provided scalar.</returns>
		[[nodiscard]] constexpr Vector4f operator*(const float scalar) const
		{
			const auto xProduct = x * scalar;
			const auto yProduct = y * scalar;
			const auto zProduct = z * scalar;
        	const auto wProduct = w * scalar;

			return Vector4f(xProduct, yProduct, zProduct, wProduct);
		}

		/// <summary>
		/// Multiplies this vector by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A reference to this vector after scaling.</returns>
		constexpr Vector4f& operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
        	w *= scalar;

			return *this;
		}

		/// <summary>
		/// Divides this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="scalar">The scalar value to divide by.</param>
		/// <returns>A new vector divided by the provided scalar.</returns>
		/// <remarks>
		/// Asserts in debug builds when the scalar is zero.
		/// </remarks>
		[[nodiscard]] constexpr Vector4f operator/(const float scalar) const
		{
			assert(scalar != 0.0f && "Vector4f::operator/ cannot divide by zero scalar");
			const auto xQuotient = x / scalar;
			const auto yQuotient = y / scalar;
			const auto zQuotient = z / scalar;
        	const auto wQuotient = w / scalar;

			return Vector4f(xQuotient, yQuotient, zQuotient, wQuotient);
		}

		/// <summary>
		/// Divides this vector by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value to divide by.</param>
		/// <returns>A reference to this vector after division.</returns>
		/// <remarks>
		/// Asserts in debug builds when the scalar is zero.
		/// </remarks>
		constexpr Vector4f& operator/=(const float scalar)
		{
			assert(scalar != 0.0f && "Vector4f::operator/= cannot divide by zero scalar");
			x /= scalar;
			y /= scalar;
			z /= scalar;
        	w /= scalar;

			return *this;
		}

		/// <summary>
		/// Multiplies this vector by another vector component by component.
		/// </summary>
		/// <param name="other">The vector containing the component values to multiply by.</param>
		/// <returns>A new vector containing the component-wise product.</returns>
		/// <remarks>
		/// This is not a dot product. Use <c>dot</c> for dot product operations.
		/// </remarks>
		[[nodiscard]] constexpr Vector4f ComponentWiseMultiply(const Vector4f& other) const
		{
			const auto xProduct = x * other.x;
			const auto yProduct = y * other.y;
			const auto zProduct = z * other.z;
        	const auto wProduct = w * other.w;

			return Vector4f(xProduct, yProduct, zProduct, wProduct);
		}

		/// <summary>
		/// Divides this vector by another vector component by component.
		/// </summary>
		/// <param name="other">The vector containing the component values to divide by.</param>
		/// <returns>A new vector containing the component-wise quotient.</returns>
		/// <remarks>
		/// Asserts in debug builds when any component of <paramref name="other"/> is zero.
		/// </remarks>
		[[nodiscard]] constexpr Vector4f ComponentWiseDivide(const Vector4f& other) const
		{
			assert(other.x != 0.0f && "Vector4f::componentWiseDivide() cannot divide by zero x component");
			assert(other.y != 0.0f && "Vector4f::componentWiseDivide() cannot divide by zero y component");
			assert(other.z != 0.0f && "Vector4f::componentWiseDivide() cannot divide by zero z component");
			assert(other.w != 0.0f && "Vector4f::componentWiseDivide() cannot divide by zero w component");
			const auto xQuotient = (x / other.x);
			const auto yQuotient = (y / other.y);
			const auto zQuotient = (z / other.z);
        	const auto wQuotient = (w / other.w);

			return Vector4f(xQuotient, yQuotient, zQuotient, wQuotient);
		}

		/// <summary>
		/// Calculates the length, or magnitude, of this vector.
		/// </summary>
		/// <returns>The length of this vector.</returns>
		[[nodiscard]] float length() const
		{
			return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
		}

		/// <summary>
		/// Calculates the squared length of this vector.
		/// </summary>
		/// <returns>The squared length of this vector.</returns>
		/// <remarks>
		/// This avoids the square root used by <c>length</c> and is useful for distance comparisons.
		/// </remarks>
		[[nodiscard]] constexpr float lengthSquared() const
		{
			return (x * x) + (y * y) + (z * z) + (w * w);
		}

		/// <summary>
		/// Calculates the dot product between this vector and another vector.
		/// </summary>
		/// <param name="other">The other vector used in the dot product calculation.</param>
		/// <returns>The dot product of the two vectors.</returns>
		[[nodiscard]] constexpr float dot(const Vector4f& other) const
		{
			return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
		}

		/// <summary>
		/// Returns a normalized copy of this vector.
		/// </summary>
		/// <returns>A new vector with the same direction and a length of one.</returns>
		/// <remarks>
		/// Asserts in debug builds when attempting to normalize a zero-length vector.
		/// </remarks>
		[[nodiscard]] Vector4f normalized() const
		{
			const float magnitude = length();
			assert(magnitude != 0.0f && "Vector4f::normalized() cannot normalize a zero vector");
			return Vector4f(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
		}
	};
}
