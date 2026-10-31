#pragma once

#include <cmath>
#include <cassert>

namespace cocoa::math
{
	/// <summary>
	/// Represents a three-dimensional vector using single-precision floating-point components.
	/// </summary>
	struct Vector3f
	{
		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };

		constexpr Vector3f() = default;

		constexpr Vector3f(const float x, const float y, const float z) :
			x(x), y(y), z(z)
		{

		}

		/// <summary>
		/// Adds another vector to this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A new vector containing the component-wise sum.</returns>
		[[nodiscard]] constexpr Vector3f operator+(const Vector3f& other) const
		{
			const auto xSum = x + other.x;
			const auto ySum = y + other.y;
			const auto zSum = z + other.z;

			return Vector3f(xSum, ySum, zSum);
		}

		/// <summary>
		/// Adds another vector to this vector.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A reference to this vector after the addition.</returns>
		constexpr Vector3f& operator+=(const Vector3f& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		/// <summary>
		/// Subtracts another vector from this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A new vector containing the component-wise difference.</returns>
		[[nodiscard]] constexpr Vector3f operator-(const Vector3f& other) const
		{
			const auto xDifference = x - other.x;
			const auto yDifference = y - other.y;
			const auto zDifference = z - other.z;

			return Vector3f(xDifference, yDifference, zDifference);
		}

		/// <summary>
		/// Subtracts another vector from this vector.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A reference to this vector after the subtraction.</returns>
		constexpr Vector3f& operator-=(const Vector3f& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		/// <summary>
		/// Multiplies this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A new vector scaled by the provided scalar.</returns>
		[[nodiscard]] constexpr Vector3f operator*(const float scalar) const
		{
			const auto xProduct = x * scalar;
			const auto yProduct = y * scalar;
			const auto zProduct = z * scalar;

			return Vector3f(xProduct, yProduct, zProduct);
		}

		/// <summary>
		/// Multiplies this vector by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A reference to this vector after scaling.</returns>
		constexpr Vector3f& operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

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
		[[nodiscard]] constexpr Vector3f operator/(const float scalar) const
		{
			assert(scalar != 0.0f && "Vector3f::operator/ cannot divide by zero scalar");
			const auto xQuotient = x / scalar;
			const auto yQuotient = y / scalar;
			const auto zQuotient = z / scalar;

			return Vector3f(xQuotient, yQuotient, zQuotient);
		}

		/// <summary>
		/// Divides this vector by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value to divide by.</param>
		/// <returns>A reference to this vector after division.</returns>
		/// <remarks>
		/// Asserts in debug builds when the scalar is zero.
		/// </remarks>
		constexpr Vector3f& operator/=(const float scalar)
		{
			assert(scalar != 0.0f && "Vector3f::operator/= cannot divide by zero scalar");
			x /= scalar;
			y /= scalar;
			z /= scalar;

			return *this;
		}

		/// <summary>
		/// Compares this vector with another vector for exact component-wise equality.
		/// </summary>
		/// <param name="other">The vector to compare against.</param>
		/// <returns>True if all components are equal; otherwise, false.</returns>
		bool operator==(const Vector3f& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		/// <summary>
		/// Multiplies this vector by another vector component by component.
		/// </summary>
		/// <param name="other">The vector containing the component values to multiply by.</param>
		/// <returns>A new vector containing the component-wise product.</returns>
		/// <remarks>
		/// This is not a dot product. Use <c>dot</c> for dot product operations.
		/// </remarks>
		[[nodiscard]] constexpr Vector3f componentWiseMultiply(const Vector3f& other) const
		{
			const auto xProduct = x * other.x;
			const auto yProduct = y * other.y;
			const auto zProduct = z * other.z;

			return Vector3f(xProduct, yProduct, zProduct);
		}

		/// <summary>
		/// Divides this vector by another vector component by component.
		/// </summary>
		/// <param name="other">The vector containing the component values to divide by.</param>
		/// <returns>A new vector containing the component-wise quotient.</returns>
		/// <remarks>
		/// Asserts in debug builds when either component of <paramref name="other"/> is zero.
		/// </remarks>
		[[nodiscard]] constexpr Vector3f componentWiseDivide(const Vector3f& other) const
		{
			assert(other.x != 0.0f && "Vector3f::componentWiseDivide() cannot divide by zero x component");
			assert(other.y != 0.0f && "Vector3f::componentWiseDivide() cannot divide by zero y component");
			assert(other.z != 0.0f && "Vector3f::componentWiseDivide() cannot divide by zero z component");
			const auto xQuotient = (x / other.x);
			const auto yQuotient = (y / other.y);
			const auto zQuotient = (z / other.z);

			return Vector3f(xQuotient, yQuotient, zQuotient);
		}

		/// <summary>
		/// Calculates the length, or magnitude, of this vector.
		/// </summary>
		/// <returns>The length of this vector.</returns>
		[[nodiscard]] float length() const
		{
			return std::sqrt((x * x) + (y * y) + (z * z));
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
			return (x * x) + (y * y) + (z * z);
		}

		/// <summary>
		/// Calculates the dot product between this vector and another vector.
		/// </summary>
		/// <param name="other">The other vector used in the dot product calculation.</param>
		/// <returns>The dot product of the two vectors.</returns>
		[[nodiscard]] constexpr float dot(const Vector3f& other) const
		{
			return (x * other.x) + (y * other.y) + (z * other.z);
		}

		/// <summary>
		/// Calculates the cross product between this vector and another vector.
		/// </summary>
		/// <param name="other">The other vector used in the cross product calculation.</param>
		/// <returns>A vector perpendicular to both vectors.</returns>
		[[nodiscard]] constexpr Vector3f cross(const Vector3f& other) const
		{
			const auto newX = (y * other.z) - (z * other.y);
			const auto newY = (z * other.x) - (x * other.z);
			const auto newZ = (x * other.y) - (y * other.x);

			return Vector3f(newX, newY, newZ);
		}

		/// <summary>
		/// Returns a normalized copy of this vector.
		/// </summary>
		/// <returns>A new vector with the same direction and a length of one.</returns>
		/// <remarks>
		/// Asserts in debug builds when attempting to normalize a zero-length vector.
		/// </remarks>
		[[nodiscard]] Vector3f normalized() const
		{
			const float magnitude = length();
			assert(magnitude != 0.0f && "Vector3f::normalized() cannot normalize a zero vector");
			return Vector3f(x / magnitude, y / magnitude, z / magnitude);
		}
	};
}
