#include <Math/Vector2f.hpp>

#include <gtest/gtest.h>

namespace Cocoa::Math::Tests
{
	struct Vector2fTestCase
	{
		Vector2f Left;
		Vector2f Right;
		Vector2f Expected;
	};

	struct Vector2fScalarTestCase
	{
		Vector2f Left;
		float Scalar;
		Vector2f Expected;
	};

	TEST(Vector2fTests, Constructor_ShouldSetComponentsToZero_WhenUsingDefaultConstructor)
	{
		const Vector2f sut;

		EXPECT_FLOAT_EQ(sut.X, 0.0f);
		EXPECT_FLOAT_EQ(sut.Y, 0.0f);
	}

	TEST(Vector2fTests, Constructor_ShouldSetComponents_WhenProvidingValues)
	{
		Vector2f sut(2.0f, 3.0f);

		EXPECT_FLOAT_EQ(sut.X, 2.0f);
		EXPECT_FLOAT_EQ(sut.Y, 3.0f);
	}

	class Vector2fAddTests : public testing::TestWithParam<Vector2fTestCase> { };
	INSTANTIATE_TEST_SUITE_P(
		Vector2fValues,
		Vector2fAddTests,
		testing::Values
		(
			Vector2fTestCase
			{
				.Left = { 1.0f, 2.0f },
				.Right = { 3.0f, 4.0f },
				.Expected = { 4.0f, 6.0f }
			},
			Vector2fTestCase
			{
				.Left = { -1.0f, -2.0f },
				.Right = { -3.0f, -4.0f },
				.Expected = { -4.0f, -6.0f }
			},
			Vector2fTestCase
			{
				.Left = { 5.0f, -2.0f },
				.Right = { -3.0f, 4.0f },
				.Expected = { 2.0f, 2.0f }
			}
		)
	);
	TEST_P(Vector2fAddTests, AddOperator_ShouldReturnSum_WhenAddingTwoVectors)
	{
		const Vector2fTestCase testCase = GetParam();

		const Vector2f result = testCase.Left + testCase.Right;

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
	}

	TEST_P(Vector2fAddTests, AddAssignOperator_ShouldMutateVector_WhenAddingOtherVector)
	{
		const Vector2fTestCase testCase = GetParam();

		Vector2f sut = testCase.Left;

		Vector2f& result = sut += testCase.Right;

		EXPECT_FLOAT_EQ(sut.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(sut.Y, testCase.Expected.Y);

		EXPECT_EQ(&result, &sut);
	}

	class Vector2fSubtractTests : public testing::TestWithParam<Vector2fTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector2fValues,
		Vector2fSubtractTests,
		testing::Values
		(
			Vector2fTestCase
			{
				.Left = { 2.0f, 4.0f },
				.Right = { 1.0f, 2.0f },
				.Expected = { 1.0f, 2.0f }
			},
			Vector2fTestCase
			{
				.Left = { -1.0f, -2.0f },
				.Right = { -3.0f, -4.0f },
				.Expected = { 2.0f, 2.0f }
			},
			Vector2fTestCase
			{
				.Left = { 5.0f, -2.0f },
				.Right = { -3.0f, 4.0f },
				.Expected = { 8.0f, -6.0f }
			}
		)
	);
	TEST_P(Vector2fSubtractTests, SubtractOperator_ShouldReturnDifference_WhenSubtractingTwoVectors)
	{
		const Vector2fTestCase testCase = GetParam();

		const Vector2f result = testCase.Left - testCase.Right;

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
	}

	TEST_P(Vector2fSubtractTests, SubtractAssignOperator_ShouldMutateVector_WhenSubtractingOtherVector)
	{
		const Vector2fTestCase testCase = GetParam();

		Vector2f sut = testCase.Left;

		Vector2f& result = sut -= testCase.Right;

		EXPECT_FLOAT_EQ(sut.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(sut.Y, testCase.Expected.Y);

		EXPECT_EQ(&result, &sut);
	}

	class Vector2MultiplyScalarTests : public testing::TestWithParam<Vector2fScalarTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector2fValues,
		Vector2MultiplyScalarTests,
		testing::Values
		(
			Vector2fScalarTestCase
			{
				.Left = { 2.0f, 18.55f },
				.Scalar = { 1.0f },
				.Expected = { 2.0f, 18.55f }
			},
			Vector2fScalarTestCase
			{
				.Left = { -55.65f, -189.4f },
				.Scalar = { -5.6f },
				.Expected = { 311.64, 1060.64f }
			},
			Vector2fScalarTestCase
			{
				.Left = { 7.8f, -28.9f },
				.Scalar = { -55.0f },
				.Expected = { -429.0f,  1589.5f }
			}
		)
	);
	TEST_P(Vector2MultiplyScalarTests, MultiplyOperator_ShouldScaleVector_WhenMultiplyingByScalar)
	{
		const Vector2fScalarTestCase testCase = GetParam();

		const Vector2f result = testCase.Left * testCase.Scalar;

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
	}

	TEST_P(Vector2MultiplyScalarTests, MultiplyAssignOperator_ShouldMutateVector_WhenMultiplyByScalar)
	{
		const Vector2fScalarTestCase testCase = GetParam();

		Vector2f sut = testCase.Left;

		Vector2f& result = sut *= testCase.Scalar;

		EXPECT_FLOAT_EQ(sut.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(sut.Y, testCase.Expected.Y);

		EXPECT_EQ(&result, &sut);
	}

	class Vector2DivideScalarTests : public testing::TestWithParam<Vector2fScalarTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector2fValues,
		Vector2DivideScalarTests,
		testing::Values
		(
			Vector2fScalarTestCase
			{
				.Left = { 12.55f, 18.55f },
				.Scalar = { 6.3f },
				.Expected = { 1.992063492f, 2.9444442f }
			},
			Vector2fScalarTestCase
			{
				.Left = { -55.65f, -189.4f },
				.Scalar = { -5.6f },
				.Expected = { 9.9375f, 33.82142857f }
			},
			Vector2fScalarTestCase
			{
				.Left = { 7.8f, -28.9f },
				.Scalar = { -55.0f },
				.Expected = { -0.14181818f,  0.52545452f }
			}
		)
	);
	TEST_P(Vector2DivideScalarTests, DivideOperator_ShouldScaleVector_WhenDividingByScalar)
	{
		const Vector2fScalarTestCase testCase = GetParam();

		const Vector2f result = testCase.Left / testCase.Scalar;

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
	}

	TEST(Vector2fTests, DivideOperator_ShouldAssert_WhenDividingByZeroScalar)
	{
		const Vector2f sut{ 10.0f, 20.0f };
		const float scalar = 0.0f;

		EXPECT_DEBUG_DEATH(
			{
				const Vector2f result = sut / scalar;
				(void)result;
			},
			"cannot divide by zero"
		);
	}

	TEST_P(Vector2DivideScalarTests, DivideAssignOperator_ShouldMutateVector_WhenMDividingByScalar)
	{
		const Vector2fScalarTestCase testCase = GetParam();

		Vector2f sut = testCase.Left;

		Vector2f& result = sut /= testCase.Scalar;

		EXPECT_FLOAT_EQ(sut.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(sut.Y, testCase.Expected.Y);

		EXPECT_EQ(&result, &sut);
	}

	TEST(Vector2fTests, DivideOperatorAssign_ShouldAssert_WhenDividingByZeroScalar)
	{
		Vector2f sut{ 10.0f, 20.0f };
		const float scalar = 0.0f;

		EXPECT_DEBUG_DEATH(
			{
				(void)(sut /= scalar);
			},
			"cannot divide by zero"
		);
	}

	class Vector2fMultiplyComponentWiseTests : public testing::TestWithParam<Vector2fTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector2fValues,
		Vector2fMultiplyComponentWiseTests,
		testing::Values
		(
			Vector2fTestCase
			{
				.Left = { 2.0f, 4.0f },
				.Right = { 1.0f, 2.0f },
				.Expected = { 2.0f, 8.0f }
			},
			Vector2fTestCase
			{
				.Left = { -5.2f, -90.65f },
				.Right = { -28.5f, -1.66f },
				.Expected = { 148.2f, 150.479f }
			},
			Vector2fTestCase
			{
				.Left = { 7.8f, -28.9f },
				.Right = { -16.47f, 13.25f },
				.Expected = { -128.466f, -382.925f }
			}
		)
	);
	TEST_P(Vector2fMultiplyComponentWiseTests, ComponentWiseMultiply_ShouldReturnProduct_WhenMultiplyingTwoVectors)
	{
		const Vector2fTestCase testCase = GetParam();

		const Vector2f result = testCase.Left.ComponentWiseMultiply(testCase.Right);

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
	}

	class Vector2fDivideComponentWiseTests : public testing::TestWithParam<Vector2fTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector2fValues,
		Vector2fDivideComponentWiseTests,
		testing::Values
		(
			Vector2fTestCase
			{
				.Left = { 2.0f, 18.55f },
				.Right = { 1.0f, 3.5f },
				.Expected = { 2.0f, 5.3f }
			},
			Vector2fTestCase
			{
				.Left = { -55.65f, -189.4f },
				.Right = { -2.87f, -2.5f },
				.Expected = { 19.3902439f, 75.76f }
			},
			Vector2fTestCase
			{
				.Left = { 7.8f, -28.9f },
				.Right = { -16.47f, 13.25f },
				.Expected = { -0.473588342f, -2.181132075f }
			}
		)
	);
	TEST_P(Vector2fDivideComponentWiseTests, ComponentWiseDivide_ShouldReturnQuotient_WhenDividingTwoVectors)
	{
		const Vector2fTestCase testCase = GetParam();

		const Vector2f result = testCase.Left.ComponentWiseDivide(testCase.Right);

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
	}

	TEST(Vector2fTests, ComponentWiseDivide_ShouldAssert_WhenDividingByZeroXComponent)
	{
		const Vector2f value{ 10.0f, 20.0f };
		const Vector2f divisor{ 0.0f, 2.0f };

		EXPECT_DEBUG_DEATH(
			{
				const Vector2f result = value.ComponentWiseDivide(divisor);
				(void)result;
			},
			"cannot divide by zero"
		);
	}

	TEST(Vector2fTests, Length_ShouldReturnMagnitude_WhenVectorHasComponent)
	{
		const Vector2f sut(3.0f, 4.0f);

		const float result = sut.Length();

		EXPECT_FLOAT_EQ(result, 5);
	}

	TEST(Vector2fTests, LengthSquared_ShouldReturnSquaredMagnitude_WhenVectorHasComponents)
	{
		const Vector2f sut{ 3.0f, 4.0f };

		const float result = sut.LengthSquared();

		EXPECT_FLOAT_EQ(result, 25.0f);
	}

	TEST(Vector2fTests, Dot_ShouldReturnDotProduct_WhenProvidingOtherVector)
	{
		const Vector2f left{ 1.0f, 2.0f };
		const Vector2f right{ 3.0f, 4.0f };

		const float result = left.Dot(right);

		EXPECT_FLOAT_EQ(result, 11.0f);
	}

	TEST(Vector2fTests, Normalized_ShouldReturnUnitVector_WhenVectorIsNonZero)
	{
		const Vector2f sut{ 3.0f, 4.0f };

		const Vector2f result = sut.Normalized();

		EXPECT_FLOAT_EQ(result.X, 0.6f);
		EXPECT_FLOAT_EQ(result.Y, 0.8f);
	}

	TEST(Vector2fTests, Normalized_ShouldAssert_WhenLengthIsZero)
	{
		const Vector2f sut{ 0.f, 0.f };

		EXPECT_DEBUG_DEATH(
			{
				const Vector2f result = sut.Normalized();
				(void)result;
			},
			"cannot normalize a zero vector"
		);
	}
}