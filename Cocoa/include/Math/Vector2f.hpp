#pragma once

#include <cmath>
#include <cassert>

namespace Cocoa::Math
{
	/// <summary>
	/// Represents a two-dimensional vector using single-precision floating-point components.
	/// </summary>
	struct Vector2f
	{
		float X{ 0.0f };
		float Y{ 0.0f };

		constexpr Vector2f() = default;

		constexpr Vector2f(const float x, const float y) :
			X(x),
			Y(y)
		{

		}

		/// <summary>
		/// Adds another vector to this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A new vector containing the component-wise sum.</returns>
		[[nodiscard]] constexpr Vector2f operator+(const Vector2f& other) const
		{
			const auto xSum = X + other.X;
			const auto ySum = Y + other.Y;

			return Vector2f(xSum, ySum);
		}

		/// <summary>
		/// Adds another vector to this vector.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A reference to this vector after the addition.</returns>
		constexpr Vector2f& operator+=(const Vector2f& other)
		{
			X += other.X;
			Y += other.Y;

			return *this;
		}

		/// <summary>
		/// Subtracts another vector from this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A new vector containing the component-wise difference.</returns>
		[[nodiscard]] constexpr Vector2f operator-(const Vector2f& other) const
		{
			const auto xDifference = X - other.X;
			const auto yDifference = Y - other.Y;

			return Vector2f(xDifference, yDifference);
		}

		/// <summary>
		/// Subtracts another vector from this vector.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A reference to this vector after the subtraction.</returns>
		constexpr Vector2f& operator-=(const Vector2f& other)
		{
			X -= other.X;
			Y -= other.Y;

			return *this;
		}

		/// <summary>
		/// Multiplies this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A new vector scaled by the provided scalar.</returns>
		[[nodiscard]] constexpr Vector2f operator*(const float scalar) const
		{
			const auto xProduct = X * scalar;
			const auto yProduct = Y * scalar;

			return Vector2f(xProduct, yProduct);
		}

		/// <summary>
		/// Multiplies this vector by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A reference to this vector after scaling.</returns>
		constexpr Vector2f& operator*=(const float scalar)
		{
			X *= scalar;
			Y *= scalar;

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
		[[nodiscard]] constexpr Vector2f operator/(const float scalar) const
		{
			assert(scalar != 0.0f && "Vector2f::operator/ cannot divide by zero scalar");
			const auto xQuotient = (X / scalar);
			const auto yQuotient = (Y / scalar);

			return Vector2f(xQuotient, yQuotient);
		}

		/// <summary>
		/// Divides this vector by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value to divide by.</param>
		/// <returns>A reference to this vector after division.</returns>
		/// <remarks>
		/// Asserts in debug builds when the scalar is zero.
		/// </remarks>
		constexpr Vector2f& operator/=(const float scalar)
		{
			assert(scalar != 0.0f && "Vector2f::operator/= cannot divide by zero scalar");
			X /= scalar;
			Y /= scalar;

			return *this;
		}

		/// <summary>
		/// Multiplies this vector by another vector component by component.
		/// </summary>
		/// <param name="other">The vector containing the component values to multiply by.</param>
		/// <returns>A new vector containing the component-wise product.</returns>
		/// <remarks>
		/// This is not a dot product. Use <c>Dot</c> for dot product operations.
		/// </remarks>
		[[nodiscard]] constexpr Vector2f ComponentWiseMultiply(const Vector2f& other) const
		{
			const auto xProduct = X * other.X;
			const auto yProduct = Y * other.Y;

			return Vector2f(xProduct, yProduct);
		}

		/// <summary>
		/// Divides this vector by another vector component by component.
		/// </summary>
		/// <param name="other">The vector containing the component values to divide by.</param>
		/// <returns>A new vector containing the component-wise quotient.</returns>
		/// <remarks>
		/// Asserts in debug builds when either component of <paramref name="other"/> is zero.
		/// </remarks>
		[[nodiscard]] constexpr Vector2f ComponentWiseDivide(const Vector2f& other) const
		{
			assert(other.X != 0.0f && "Vector2f::ComponentWiseDivide() cannot divide by zero X component");
			assert(other.Y != 0.0f && "Vector2f::ComponentWiseDivide() cannot divide by zero Y component");
			const auto xQuotient = (X / other.X);
			const auto yQuotient = (Y / other.Y);

			return Vector2f(xQuotient, yQuotient);
		}

		/// <summary>
		/// Calculates the length, or magnitude, of this vector.
		/// </summary>
		/// <returns>The length of this vector.</returns>
		[[nodiscard]] float Length() const
		{
			return std::sqrt(LengthSquared());
		}

		/// <summary>
		/// Calculates the squared length of this vector.
		/// </summary>
		/// <returns>The squared length of this vector.</returns>
		/// <remarks>
		/// This avoids the square root used by <c>Length</c> and is useful for distance comparisons.
		/// </remarks>
		[[nodiscard]] constexpr float LengthSquared() const
		{
			return X * X + Y * Y;
		}

		/// <summary>
		/// Calculates the dot product between this vector and another vector.
		/// </summary>
		/// <param name="other">The other vector used in the dot product calculation.</param>
		/// <returns>The dot product of the two vectors.</returns>
		[[nodiscard]] constexpr float Dot(const Vector2f& other) const
		{
			return (X * other.X) + (Y * other.Y);
		}

		/// <summary>
		/// Returns a normalized copy of this vector.
		/// </summary>
		/// <returns>A new vector with the same direction and a length of one.</returns>
		/// <remarks>
		/// Asserts in debug builds when attempting to normalize a zero-length vector.
		/// </remarks>
		[[nodiscard]] Vector2f Normalized() const
		{
			const float magnitude = Length();
			assert(magnitude != 0.0f && "Vector2f::Normalized() cannot normalize a zero vector");
			return Vector2f(X / magnitude, Y / magnitude);
		}
	};
}