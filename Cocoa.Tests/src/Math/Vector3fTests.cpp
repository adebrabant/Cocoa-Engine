#include <Math/Vector3f.hpp>

#include <gtest/gtest.h>

namespace Cocoa::Math::Tests
{
	struct Vector3fTestCase
	{
		Vector3f Left;
		Vector3f Right;
		Vector3f Expected;
	};

	struct Vector3fScalarTestCase
	{
		Vector3f Left;
		float Scalar;
		Vector3f Expected;
	};

	TEST(Vector3fTests, Constructor_ShouldSetComponentsToZero_WhenUsingDefaultConstructor)
	{
		const Vector3f sut;

		EXPECT_FLOAT_EQ(sut.X, 0.0f);
		EXPECT_FLOAT_EQ(sut.Y, 0.0f);
		EXPECT_FLOAT_EQ(sut.Z, 0.0f);
	}

	TEST(Vector3fTests, Constructor_ShouldSetComponents_WhenProvidingValues)
	{
		const float expectedX = 2.0f;
		const float expectedY = 3.0f;
		const float expectedZ = 5.0f;

		const Vector3f sut(expectedX, expectedY, expectedZ);

		EXPECT_FLOAT_EQ(sut.X, expectedX);
		EXPECT_FLOAT_EQ(sut.Y, expectedY);
		EXPECT_FLOAT_EQ(sut.Z, expectedZ);
	}

	class Vector3fAddTests : public testing::TestWithParam<Vector3fTestCase> { };
	INSTANTIATE_TEST_SUITE_P(
		Vector3fValues,
		Vector3fAddTests,
		testing::Values
		(
			Vector3fTestCase 
			{
				.Left{ 1.0f, 2.0f, 6.0f },
				.Right{ 3.0f, 4.0f, 10.5f },
				.Expected{ 4.0f, 6.0f, 16.5f}
			},
			Vector3fTestCase
			{
				.Left{ -1.0f, -2.0f, -4.0f},
				.Right{ -3.0f, -4.0f, -9.0f},
				.Expected{ -4.0f, -6.0f, -13.0f}
			},
			Vector3fTestCase
			{
				.Left{ 5.0f, -2.0f, 12.0f },
				.Right{ -3.0f, 4.0f, -3.0f },
				.Expected{ 2.0f, 2.0f, 9.0f }
			}
		)
	);

	TEST_P(Vector3fAddTests, AddOperator_ShouldReturnSum_WhenAddingTwoVectors)
	{
		const Vector3fTestCase testCase = GetParam();

		const Vector3f result = testCase.Left + testCase.Right;

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	TEST_P(Vector3fAddTests, AddAssignOperator_ShouldMutateVector_WhenAddingOtherVector)
	{
		const Vector3fTestCase testCase = GetParam();
		Vector3f sut = testCase.Left;

		Vector3f& result = sut += testCase.Right;

		EXPECT_EQ(&result, &sut);
		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	class Vector3fSubtractTests : public testing::TestWithParam<Vector3fTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector3fValues,
		Vector3fSubtractTests,
		testing::Values
		(
			Vector3fTestCase
			{
				.Left{ 2.0f, 4.0f, 8.0f },
				.Right{ 1.0f, 2.0f, 14.5f },
				.Expected{ 1.0f, 2.0f, -6.5f }
			},
			Vector3fTestCase
			{
				.Left{ -1.0f, -2.0f, -4.0f },
				.Right{ -3.0f, -4.0f, -11.7f },
				.Expected{ 2.0f, 2.0f, 7.7f }
			},
			Vector3fTestCase
			{
				.Left{ 5.0f, -2.0f, -21.2f },
				.Right{ -3.0f, 4.0f, 11.2f },
				.Expected{ 8.0f, -6.0f, -32.400002f }
			}
		)
	);

	TEST_P(Vector3fSubtractTests, SubtractOperator_ShouldReturnDifference_WhenSubtractingTwoVectors)
	{
		const Vector3fTestCase testCase = GetParam();

		const Vector3f result = testCase.Left - testCase.Right;

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	TEST_P(Vector3fSubtractTests, SubtractAssignOperator_ShouldMutateVector_WhenSubtractingOtherVector)
	{
		const Vector3fTestCase testCase = GetParam();
		Vector3f sut = testCase.Left;

		Vector3f& result = sut -= testCase.Right;

		EXPECT_EQ(&result, &sut);
		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	class Vector3fMultiplyScalarTests : public testing::TestWithParam<Vector3fScalarTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector3fValues,
		Vector3fMultiplyScalarTests,
		testing::Values
		(
			Vector3fScalarTestCase
			{
				.Left{ 2.0f, 18.55f, 23.5f },
				.Scalar{ 1.0f },
				.Expected{ 2.0f, 18.55f, 23.5f }
			},
			Vector3fScalarTestCase
			{
				.Left{ -55.65f, -189.4f, 20.4f },
				.Scalar{ -5.6f },
				.Expected{ 311.64, 1060.64f, -114.24f }
			},
			Vector3fScalarTestCase
			{
				.Left{ 7.8f, -28.9f,  15.4f},
				.Scalar{ -55.0f },
				.Expected{ -429.0f, 1589.5f, -847.0f}
			}
		)
	);

	TEST_P(Vector3fMultiplyScalarTests, MultiplyOperator_ShouldScaleVector_WhenMultiplyingByScalar)
	{
		const Vector3fScalarTestCase testCase = GetParam();

		const Vector3f result = testCase.Left * testCase.Scalar;

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	TEST_P(Vector3fMultiplyScalarTests, MultiplyAssignOperator_ShouldMutateVector_WhenMultiplyByScalar)
	{
		const Vector3fScalarTestCase testCase = GetParam();
		Vector3f sut = testCase.Left;

		Vector3f& result = sut *= testCase.Scalar;

		EXPECT_EQ(&result, &sut);
		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	class Vector3fDivideScalarTests : public testing::TestWithParam<Vector3fScalarTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector3fValues,
		Vector3fDivideScalarTests,
		testing::Values
		(
			Vector3fScalarTestCase
			{
				.Left{ 12.55f, 18.55f, 23.5f },
				.Scalar{ 6.3f },
				.Expected{ 1.992063492f, 2.9444442f, 3.73015873f }
			},
			Vector3fScalarTestCase
			{
				.Left{ -55.65f, -189.4f, -11.7f },
				.Scalar{ -5.6f },
				.Expected{ 9.9375f, 33.82142857f, 2.089285714f }
			},
			Vector3fScalarTestCase
			{
				.Left{ 7.8f, -28.9f, 500.7f },
				.Scalar{ -55.0f },
				.Expected{ -0.14181818f,  0.52545452f, -9.103636364f }
			}
		)
	);

	TEST_P(Vector3fDivideScalarTests, DivideOperator_ShouldScaleVector_WhenDividingByScalar)
	{
		const Vector3fScalarTestCase testCase = GetParam();

		const Vector3f result = testCase.Left / testCase.Scalar;

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	TEST(Vector3fTests, DivideOperator_ShouldAssert_WhenDividingByZeroScalar)
	{
		const Vector3f sut{ 10.0f, 20.0f, 2.0f };
		const float scalar = 0.0f;

		EXPECT_DEBUG_DEATH(
			{
				const Vector3f result = sut / scalar;
				(void)result;
			},
			"cannot divide by zero"
		);
	}

	TEST_P(Vector3fDivideScalarTests, DivideAssignOperator_ShouldMutateVector_WhenDividingByScalar)
	{
		const Vector3fScalarTestCase testCase = GetParam();
		Vector3f sut = testCase.Left;

		Vector3f& result = sut /= testCase.Scalar;

		EXPECT_EQ(&sut, &result);
		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	TEST(Vector3fTests, DivideAssignOperator_ShouldAssert_WhenDividingByZeroScalar)
	{
		Vector3f sut{ 10.0f, 20.0f, 2.0f };
		const float scalar = 0.0f;

		EXPECT_DEBUG_DEATH(
			{
				(void)(sut /= scalar);
			},
			"cannot divide by zero"
		);
	}

	class Vector3fMultiplyComponentWiseTests : public testing::TestWithParam<Vector3fTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector3fValues,
		Vector3fMultiplyComponentWiseTests,
		testing::Values
		(
			Vector3fTestCase
			{
				.Left{ 2.0f, 4.0f, 7.0f },
				.Right{ 1.0f, 2.0f, 3.0f },
				.Expected{ 2.0f, 8.0f, 21.0f }
			},
			Vector3fTestCase
			{
				.Left = { -5.2f, -90.65f, -23.55f },
				.Right = { -28.5f, -1.66f, -3.44f },
				.Expected = { 148.2f, 150.479f, 81.012f }
			},
			Vector3fTestCase
			{
				.Left = { 7.8f, -28.9f, 13.5f },
				.Right = { -16.47f, 13.25f, 18.9f },
				.Expected = { -128.466f, -382.925f, 255.15f }
			}
		)
	);

	TEST_P(Vector3fMultiplyComponentWiseTests, ComponentWiseMultiply_ShouldReturnProduct_WhenMultiplyingTwoVectors)
	{
		const Vector3fTestCase testCase = GetParam();

		const Vector3f result = testCase.Left.ComponentWiseMultiply(testCase.Right);

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	class Vector3fDivideComponentWiseTests : public testing::TestWithParam<Vector3fTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector3fValues,
		Vector3fDivideComponentWiseTests,
		testing::Values
		(
			Vector3fTestCase
			{
				.Left = { 2.0f, 18.55f, 10.0f },
				.Right = { 1.0f, 3.5f, 2.0f },
				.Expected = { 2.0f, 5.3f, 5.0f }
			},
			Vector3fTestCase
			{
				.Left = { -55.65f, -189.4f, -88.6f },
				.Right = { -2.87f, -2.5f, -42.6f },
				.Expected = { 19.3902439f, 75.76f,  2.079812207f }
			},
			Vector3fTestCase
			{
				.Left = { 7.8f, -28.9f, 13.4f },
				.Right = { -16.47f, 13.25f, -33.0f },
				.Expected = { -0.473588342f, -2.181132075f, -0.4060606060f }
			}
		)
	);

	TEST_P(Vector3fDivideComponentWiseTests, ComponentWiseDivide_ShouldReturnQuotient_WhenDividingTwoVectors)
	{
		const Vector3fTestCase testCase = GetParam();

		const Vector3f result = testCase.Left.ComponentWiseDivide(testCase.Right);

		EXPECT_FLOAT_EQ(result.X, testCase.Expected.X);
		EXPECT_FLOAT_EQ(result.Y, testCase.Expected.Y);
		EXPECT_FLOAT_EQ(result.Z, testCase.Expected.Z);
	}

	TEST(Vector3fTests, ComponentWiseDivide_ShouldAssert_WhenDividingByZeroXComponent)
	{
		const Vector3f value{ 10.0f, 20.0f, 102.0f };
		const Vector3f divisor{ 0.0f, 2.0f, 0.0f };

		EXPECT_DEBUG_DEATH(
			{
				const Vector3f result = value.ComponentWiseDivide(divisor);
				(void)result;
			},
			"cannot divide by zero"
		);
	}

	TEST(Vector3fTests, Length_ShouldReturnMagnitude_WhenVectorHasComponent)
	{
		const Vector3f sut(2.0f, 3.0f, 6.0f);

		const float result = sut.Length();

		EXPECT_FLOAT_EQ(result, 7.0f);
	}

	TEST(Vector3fTests, LengthSquared_ShouldReturnSquaredMagnitude_WhenVectorHasComponents)
	{
		const Vector3f sut{ 3.0f, 4.0f, 3.0f };

		const float result = sut.LengthSquared();

		EXPECT_FLOAT_EQ(result, 34.0f);
	}

	TEST(Vector3fTests, Dot_ShouldReturnDotProduct_WhenProvidingOtherVector)
	{
		const Vector3f left{ 1.0f, 2.0f, 2.0f };
		const Vector3f right{ 3.0f, 4.0f, 3.0f };

		const float result = left.Dot(right);

		EXPECT_FLOAT_EQ(result, 17.0f);
	}

	TEST(Vector3fTests, Cross_ShouldReturnCrossProduct_WhenProvidingOtherVector)
	{
		const Vector3f sut{ 2.0f, 3.0f, 4.0f };
		const Vector3f other{ 5.0f, 6.0f, 7.0f };

		const Vector3f result = sut.Cross(other);

		EXPECT_FLOAT_EQ(result.X, -3.0f);
		EXPECT_FLOAT_EQ(result.Y, 6.0f);
		EXPECT_FLOAT_EQ(result.Z, -3.0f);
	}

	TEST(Vector3fTests, Normalized_ShouldReturnUnitVector_WhenVectorIsNonZero)
	{
		const Vector3f sut{ 2.0f, 3.0f, 4.0f };

		const Vector3f result = sut.Normalized();

		EXPECT_FLOAT_EQ(result.X, 0.37139067f);
		EXPECT_FLOAT_EQ(result.Y, 0.55708605f);
		EXPECT_FLOAT_EQ(result.Z, 0.74278134f);
	}

	TEST(Vector3fTests, Normalized_ShouldAssert_WhenLengthIsZero)
	{
		const Vector3f sut{ 0.f, 0.f, 0.0f };

		EXPECT_DEBUG_DEATH(
			{
				const Vector3f result = sut.Normalized();
				(void)result;
			},
			"cannot normalize a zero vector"
		);
	}
}