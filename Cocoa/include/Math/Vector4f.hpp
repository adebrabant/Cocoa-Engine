#pragma once

#include <cassert>
#include <cmath>

namespace Cocoa::Math
{
    /// <summary>
    /// Represents a four-dimensional vector using single-precision floating-point components.
    /// </summary>
    struct Vector4f
    {
        float X{0.0f};
        float Y{0.0f};
        float Z{0.0f};
        float W{0.0f};

        constexpr Vector4f() = default;

        constexpr Vector4f(const float x, const float y, const float z, const float w) :
            X(x), Y(y), Z(z), W(w)
        {

        }

    	/// <summary>
		/// Adds another vector to this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A new vector containing the component-wise sum.</returns>
		[[nodiscard]] constexpr Vector4f operator+(const Vector4f& other) const
		{
			const auto xSum = X + other.X;
			const auto ySum = Y + other.Y;
			const auto zSum = Z + other.Z;
        	const auto wSum = W + other.W;

			return Vector4f(xSum, ySum, zSum, wSum);
		}

		/// <summary>
		/// Adds another vector to this vector.
		/// </summary>
		/// <param name="other">The vector to add.</param>
		/// <returns>A reference to this vector after the addition.</returns>
		constexpr Vector4f& operator+=(const Vector4f& other)
		{
			X += other.X;
			Y += other.Y;
			Z += other.Z;
        	W += other.W;

			return *this;
		}

		/// <summary>
		/// Subtracts another vector from this vector and returns the result.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A new vector containing the component-wise difference.</returns>
		[[nodiscard]] constexpr Vector4f operator-(const Vector4f& other) const
		{
			const auto xDifference = X - other.X;
			const auto yDifference = Y - other.Y;
			const auto zDifference = Z - other.Z;
        	const auto wDifference = W - other.W;

			return Vector4f(xDifference, yDifference, zDifference, wDifference);
		}

		/// <summary>
		/// Subtracts another vector from this vector.
		/// </summary>
		/// <param name="other">The vector to subtract.</param>
		/// <returns>A reference to this vector after the subtraction.</returns>
		constexpr Vector4f& operator-=(const Vector4f& other)
		{
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;
        	W -= other.W;

			return *this;
		}

		/// <summary>
		/// Multiplies this vector by a scalar and returns the result.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A new vector scaled by the provided scalar.</returns>
		[[nodiscard]] constexpr Vector4f operator*(const float scalar) const
		{
			const auto xProduct = X * scalar;
			const auto yProduct = Y * scalar;
			const auto zProduct = Z * scalar;
        	const auto wProduct = W * scalar;

			return Vector4f(xProduct, yProduct, zProduct, wProduct);
		}

		/// <summary>
		/// Multiplies this vector by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value to multiply by.</param>
		/// <returns>A reference to this vector after scaling.</returns>
		constexpr Vector4f& operator*=(const float scalar)
		{
			X *= scalar;
			Y *= scalar;
			Z *= scalar;
        	W *= scalar;

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
			const auto xQuotient = X / scalar;
			const auto yQuotient = Y / scalar;
			const auto zQuotient = Z / scalar;
        	const auto wQuotient = W / scalar;

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
			X /= scalar;
			Y /= scalar;
			Z /= scalar;
        	W /= scalar;

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
		[[nodiscard]] constexpr Vector4f ComponentWiseMultiply(const Vector4f& other) const
		{
			const auto xProduct = X * other.X;
			const auto yProduct = Y * other.Y;
			const auto zProduct = Z * other.Z;
        	const auto wProduct = W * other.W;

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
			assert(other.X != 0.0f && "Vector4f::ComponentWiseDivide() cannot divide by zero X component");
			assert(other.Y != 0.0f && "Vector4f::ComponentWiseDivide() cannot divide by zero Y component");
			assert(other.Z != 0.0f && "Vector4f::ComponentWiseDivide() cannot divide by zero Z component");
			assert(other.W != 0.0f && "Vector4f::ComponentWiseDivide() cannot divide by zero W component");
			const auto xQuotient = (X / other.X);
			const auto yQuotient = (Y / other.Y);
			const auto zQuotient = (Z / other.Z);
        	const auto wQuotient = (W / other.W);

			return Vector4f(xQuotient, yQuotient, zQuotient, wQuotient);
		}

		/// <summary>
		/// Calculates the length, or magnitude, of this vector.
		/// </summary>
		/// <returns>The length of this vector.</returns>
		[[nodiscard]] float Length() const
		{
			return std::sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
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
			return (X * X) + (Y * Y) + (Z * Z) + (W * W);
		}

		/// <summary>
		/// Calculates the dot product between this vector and another vector.
		/// </summary>
		/// <param name="other">The other vector used in the dot product calculation.</param>
		/// <returns>The dot product of the two vectors.</returns>
		[[nodiscard]] constexpr float Dot(const Vector4f& other) const
		{
			return (X * other.X) + (Y * other.Y) + (Z * other.Z) + (W * other.W);
		}

		/// <summary>
		/// Returns a normalized copy of this vector.
		/// </summary>
		/// <returns>A new vector with the same direction and a length of one.</returns>
		/// <remarks>
		/// Asserts in debug builds when attempting to normalize a zero-length vector.
		/// </remarks>
		[[nodiscard]] Vector4f Normalized() const
		{
			const float magnitude = Length();
			assert(magnitude != 0.0f && "Vector4f::Normalized() cannot normalize a zero vector");
			return Vector4f(X / magnitude, Y / magnitude, Z / magnitude, W / magnitude);
		}
	};
}
