#pragma once

#include <cmath>
#include <cassert>

namespace Cocoa::Math
{
	/// <summary>
	/// Represents a three-dimensional vector using single-precision floating-point components.
	/// </summary>
	struct Vector3f
	{
		float X{ 0.0f };
		float Y{ 0.0f };
		float Z{ 0.0f };

		constexpr Vector3f() = default;

		constexpr Vector3f(float x, float y, float z) :
			X(x), Y(y), Z(z)
		{

		}

		/// <summary>
		/// Adds another vector to this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A new vector containing the component-wise sum.</returns>
		[[nodiscard]] Vector3f operator+(const Vector3f& other) const
		{
			const auto xSum = X + other.X;
			const auto ySum = Y + other.Y;
			const auto zSum = Z + other.Z;

			return Vector3f(xSum, ySum, zSum);
		}

		/// <summary>
		/// Adds another vector to this vector.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A reference to this vector after the addition.</returns>
		Vector3f& operator+=(const Vector3f& other)
		{
			X += other.X;
			Y += other.Y;
			Z += other.Z;

			return *this;
		}

		/// <summary>
		/// Subtracts another vector from this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A new vector containing the component-wise difference.</returns>
		[[nodiscard]] Vector3f operator-(const Vector3f& other) const
		{
			const auto xDifference = X - other.X;
			const auto yDifference = Y - other.Y;
			const auto zDifference = Z - other.Z;

			return Vector3f(xDifference, yDifference, zDifference);
		}

		/// <summary>
		/// Subtracts another vector from this vector.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A reference to this vector after the subtraction.</returns>
		Vector3f& operator-=(const Vector3f& other)
		{
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;

			return *this;
		}

		/// <summary>
		/// Multiplies this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A new vector scaled by the provided scalar.</returns>
		[[nodiscard]] Vector3f operator*(float scalar) const
		{
			const auto xProduct = X * scalar;
			const auto yProduct = Y * scalar;
			const auto zProduct = Z * scalar;

			return Vector3f(xProduct, yProduct, zProduct);
		}

		/// <summary>
		/// Multiplies this vector by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A reference to this vector after scaling.</returns>
		Vector3f& operator*=(float scalar)
		{
			X *= scalar;
			Y *= scalar;
			Z *= scalar;

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
		[[nodiscard]] Vector3f operator/(float scalar) const
		{
			assert(scalar != 0.0f && "Vector3f::operator/ cannot divide by zero scalar");
			const auto xQuotient = X / scalar;
			const auto yQuotient = Y / scalar;
			const auto zQuotient = Z / scalar;

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
		Vector3f& operator/=(float scalar)
		{
			assert(scalar != 0.0f && "Vector3f::operator/= cannot divide by zero scalar");
			X /= scalar;
			Y /= scalar;
			Z /= scalar;

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
		[[nodiscard]] Vector3f ComponentWiseMultiply(const Vector3f& other) const
		{
			const auto xProduct = X * other.X;
			const auto yProduct = Y * other.Y;
			const auto zProduct = Z * other.Z;

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
		[[nodiscard]] Vector3f ComponentWiseDivide(const Vector3f& other) const
		{
			assert(other.X != 0.0f && "Vector3f::ComponentWiseDivide() cannot divide by zero X component");
			assert(other.Y != 0.0f && "Vector3f::ComponentWiseDivide() cannot divide by zero Y component");
			assert(other.Z != 0.0f && "Vector3f::ComponentWiseDivide() cannot divide by zero Z component");
			const auto xQuotient = (X / other.X);
			const auto yQuotient = (Y / other.Y);
			const auto zQuotient = (Z / other.Z);

			return Vector3f(xQuotient, yQuotient, zQuotient);
		}

		/// <summary>
		/// Calculates the length, or magnitude, of this vector.
		/// </summary>
		/// <returns>The length of this vector.</returns>
		[[nodiscard]] float Length() const
		{
			return std::sqrt((X * X) + (Y * Y) + (Z * Z));
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
			return (X * X) + (Y * Y) + (Z * Z);
		}

		/// <summary>
		/// Calculates the dot product between this vector and another vector.
		/// </summary>
		/// <param name="other">The other vector used in the dot product calculation.</param>
		/// <returns>The dot product of the two vectors.</returns>
		[[nodiscard]] constexpr float Dot(const Vector3f& other) const
		{
			return (X * other.X) + (Y * other.Y) + (Z * other.Z);
		}

		/// <summary>
		/// Calculates the cross product between this vector and another vector.
		/// </summary>
		/// <param name="other">The other vector used in the cross product calculation.</param>
		/// <returns>A vector perpendicular to both vectors.</returns>
		[[nodiscard]] constexpr Vector3f Cross(const Vector3f& other) const
		{
			const auto x = (Y * other.Z) - (Z * other.Y);
			const auto y = (Z * other.X) - (X * other.Z);
			const auto z = (X * other.Y) - (Y * other.X);

			return Vector3f(x, y, z);
		}

		/// <summary>
		/// Returns a normalized copy of this vector.
		/// </summary>
		/// <returns>A new vector with the same direction and a length of one.</returns>
		/// <remarks>
		/// Asserts in debug builds when attempting to normalize a zero-length vector.
		/// </remarks>
		[[nodiscard]] Vector3f Normalized() const
		{
			const float magnitude = Length();
			assert(magnitude != 0.0f && "Vector3f::Normalized() cannot normalize a zero vector");
			return Vector3f(X / magnitude, Y / magnitude, Z / magnitude);
		}
	};
}