#include <math/Vector4f.hpp>

#include <gtest/gtest.h>

namespace cocoa_tests::math
{
	struct Vector4fTestCase
	{
		cocoa::math::Vector4f Left;
		cocoa::math::Vector4f Right;
		cocoa::math::Vector4f Expected;
	};

	struct Vector4fScalarTestCase
	{
		cocoa::math::Vector4f Left;
		float Scalar;
		cocoa::math::Vector4f Expected;
	};

	TEST(Vector4fTests, Constructor_ShouldSetComponentsToZero_WhenUsingDefaultConstructor)
	{
		const cocoa::math::Vector4f sut;

		EXPECT_FLOAT_EQ(sut.x, 0.0f);
		EXPECT_FLOAT_EQ(sut.y, 0.0f);
		EXPECT_FLOAT_EQ(sut.z, 0.0f);
	}

	TEST(Vector4fTests, Constructor_ShouldSetComponents_WhenProvidingValues)
	{
		const float expectedX = 2.0f;
		const float expectedY = 3.0f;
		const float expectedZ = 5.0f;
		const float expectedW = 1.0f;

		const cocoa::math::Vector4f sut(expectedX, expectedY, expectedZ, expectedW);

		EXPECT_FLOAT_EQ(sut.x, expectedX);
		EXPECT_FLOAT_EQ(sut.y, expectedY);
		EXPECT_FLOAT_EQ(sut.z, expectedZ);
		EXPECT_FLOAT_EQ(sut.w, expectedW);
	}

	class Vector4fAddTests : public testing::TestWithParam<Vector4fTestCase> { };
	INSTANTIATE_TEST_SUITE_P(
		Vector4fValues,
		Vector4fAddTests,
		testing::Values
		(
			Vector4fTestCase
			{
				.Left{ 1.0f, 2.0f, 6.0f, 0.0 },
				.Right{ 3.0f, 4.0f, 10.5f, 1.0f },
				.Expected{ 4.0f, 6.0f, 16.5f, 1.0f }
			},
			Vector4fTestCase
			{
				.Left{ -1.0f, -2.0f, -4.0f, 1.0f},
				.Right{ -3.0f, -4.0f, -9.0f, 0.0f },
				.Expected{ -4.0f, -6.0f, -13.0f, 1.0f }
			},
			Vector4fTestCase
			{
				.Left{ 5.0f, -2.0f, 12.0f, 0.0f },
				.Right{ -3.0f, 4.0f, -3.0f, 0.0f },
				.Expected{ 2.0f, 2.0f, 9.0f, 0.0f }
			}
		)
	);

	TEST_P(Vector4fAddTests, AddOperator_ShouldReturnSum_WhenAddingTwoVectors)
	{
		const Vector4fTestCase testCase = GetParam();

		const cocoa::math::Vector4f result = testCase.Left + testCase.Right;

		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
		EXPECT_FLOAT_EQ(result.w, testCase.Expected.w);
	}

	TEST_P(Vector4fAddTests, AddAssignOperator_ShouldMutateVector_WhenAddingOtherVector)
	{
		const Vector4fTestCase testCase = GetParam();
		cocoa::math::Vector4f sut = testCase.Left;

		cocoa::math::Vector4f& result = sut += testCase.Right;

		EXPECT_EQ(&result, &sut);
		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
		EXPECT_FLOAT_EQ(result.w, testCase.Expected.w);
	}

	class Vector4fSubtractTests : public testing::TestWithParam<Vector4fTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector4fValues,
		Vector4fSubtractTests,
		testing::Values
		(
			Vector4fTestCase
			{
				.Left{ 2.0f, 4.0f, 8.0f, 0.0f },
				.Right{ 1.0f, 2.0f, 14.5f, 1.0f },
				.Expected{ 1.0f, 2.0f, -6.5f, -1.0f }
			},
			Vector4fTestCase
			{
				.Left{ -1.0f, -2.0f, -4.0f, 0.0f },
				.Right{ -3.0f, -4.0f, -11.7f, 0.0f },
				.Expected{ 2.0f, 2.0f, 7.7f, 0.0f }
			},
			Vector4fTestCase
			{
				.Left{ 5.0f, -2.0f, -21.2f, 1.0f },
				.Right{ -3.0f, 4.0f, 11.2f, 1.0f },
				.Expected{ 8.0f, -6.0f, -32.400002f, 0.0f }
			}
		)
	);

	TEST_P(Vector4fSubtractTests, SubtractOperator_ShouldReturnDifference_WhenSubtractingTwoVectors)
	{
		const Vector4fTestCase testCase = GetParam();

		const cocoa::math::Vector4f result = testCase.Left - testCase.Right;

		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
		EXPECT_FLOAT_EQ(result.w, testCase.Expected.w);
	}

	TEST_P(Vector4fSubtractTests, SubtractAssignOperator_ShouldMutateVector_WhenSubtractingOtherVector)
	{
		const Vector4fTestCase testCase = GetParam();
		cocoa::math::Vector4f sut = testCase.Left;

		cocoa::math::Vector4f& result = sut -= testCase.Right;

		EXPECT_EQ(&result, &sut);
		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
		EXPECT_FLOAT_EQ(result.w, testCase.Expected.w);
	}

	class Vector4fMultiplyScalarTests : public testing::TestWithParam<Vector4fScalarTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector4fValues,
		Vector4fMultiplyScalarTests,
		testing::Values
		(
			Vector4fScalarTestCase
			{
				.Left{ 2.0f, 18.55f, 23.5f, 1.0f },
				.Scalar{ 1.0f },
				.Expected{ 2.0f, 18.55f, 23.5f, 1.0f }
			},
			Vector4fScalarTestCase
			{
				.Left{ -55.65f, -189.4f, 20.4f, 1.0f },
				.Scalar{ -5.6f },
				.Expected{ 311.64, 1060.64f, -114.24f, -5.6f }
			},
			Vector4fScalarTestCase
			{
				.Left{ 7.8f, -28.9f,  15.4f, 0.0f},
				.Scalar{ -55.0f },
				.Expected{ -429.0f, 1589.5f, -847.0f, 0.0f }
			}
		)
	);

	TEST_P(Vector4fMultiplyScalarTests, MultiplyOperator_ShouldScaleVector_WhenMultiplyingByScalar)
	{
		const Vector4fScalarTestCase testCase = GetParam();

		const cocoa::math::Vector4f result = testCase.Left * testCase.Scalar;

		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
		EXPECT_FLOAT_EQ(result.w, testCase.Expected.w);
	}

	TEST_P(Vector4fMultiplyScalarTests, MultiplyAssignOperator_ShouldMutateVector_WhenMultiplyByScalar)
	{
		const Vector4fScalarTestCase testCase = GetParam();
		cocoa::math::Vector4f sut = testCase.Left;

		cocoa::math::Vector4f& result = sut *= testCase.Scalar;

		EXPECT_EQ(&result, &sut);
		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
		EXPECT_FLOAT_EQ(result.w, testCase.Expected.w);
	}

	class Vector4fDivideScalarTests : public testing::TestWithParam<Vector4fScalarTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector4fValues,
		Vector4fDivideScalarTests,
		testing::Values
		(
			Vector4fScalarTestCase
			{
				.Left{ 12.55f, 18.55f, 23.5f, 1.0f },
				.Scalar{ 6.3f },
				.Expected{ 1.992063492f, 2.9444442f, 3.73015873f, 0.15873015f }
			},
			Vector4fScalarTestCase
			{
				.Left{ -55.65f, -189.4f, -11.7f, 0.0f },
				.Scalar{ -5.6f },
				.Expected{ 9.9375f, 33.82142857f, 2.089285714f, 0.0f }
			},
			Vector4fScalarTestCase
			{
				.Left{ 7.8f, -28.9f, 500.7f, 2.0f },
				.Scalar{ -55.0f },
				.Expected{ -0.14181818f,  0.52545452f, -9.103636364f, -0.036363635f }
			}
		)
	);

	TEST_P(Vector4fDivideScalarTests, DivideOperator_ShouldScaleVector_WhenDividingByScalar)
	{
		const Vector4fScalarTestCase testCase = GetParam();

		const cocoa::math::Vector4f result = testCase.Left / testCase.Scalar;

		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
		EXPECT_FLOAT_EQ(result.w, testCase.Expected.w);
	}

	TEST(Vector4fTests, DivideOperator_ShouldAssert_WhenDividingByZeroScalar)
	{
		const cocoa::math::Vector4f sut{ 10.0f, 20.0f, 2.0f, 1.0f };
		const float scalar = 0.0f;

		EXPECT_DEBUG_DEATH(
			{
				const cocoa::math::Vector4f result = sut / scalar;
				(void)result;
			},
			"cannot divide by zero"
		);
	}

	TEST_P(Vector4fDivideScalarTests, DivideAssignOperator_ShouldMutateVector_WhenDividingByScalar)
	{
		const Vector4fScalarTestCase testCase = GetParam();
		cocoa::math::Vector4f sut = testCase.Left;

		cocoa::math::Vector4f& result = sut /= testCase.Scalar;

		EXPECT_EQ(&sut, &result);
		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
	}

	TEST(Vector4fTests, DivideAssignOperator_ShouldAssert_WhenDividingByZeroScalar)
	{
		cocoa::math::Vector4f sut{ 10.0f, 20.0f, 2.0f, 1.0f };
		const float scalar = 0.0f;

		EXPECT_DEBUG_DEATH(
			{
				(void)(sut /= scalar);
			},
			"cannot divide by zero"
		);
	}

	class Vector4fMultiplyComponentWiseTests : public testing::TestWithParam<Vector4fTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector4fValues,
		Vector4fMultiplyComponentWiseTests,
		testing::Values
		(
			Vector4fTestCase
			{
				.Left{ 2.0f, 4.0f, 7.0f, 1.0f },
				.Right{ 1.0f, 2.0f, 3.0f, 1.0f },
				.Expected{ 2.0f, 8.0f, 21.0f, 1.0f }
			},
			Vector4fTestCase
			{
				.Left = { -5.2f, -90.65f, -23.55f, 0.0f },
				.Right = { -28.5f, -1.66f, -3.44f, 0.0f },
				.Expected = { 148.2f, 150.479f, 81.012f, 0.0f }
			},
			Vector4fTestCase
			{
				.Left = { 7.8f, -28.9f, 13.5, 2.0f },
				.Right = { -16.47f, 13.25f, 18.9f, 2.0f },
				.Expected = { -128.466f, -382.925f, 255.15f, 4.0f }
			}
		)
	);

	TEST_P(Vector4fMultiplyComponentWiseTests, ComponentWiseMultiply_ShouldReturnProduct_WhenMultiplyingTwoVectors)
	{
		const Vector4fTestCase testCase = GetParam();

		const cocoa::math::Vector4f result = testCase.Left.ComponentWiseMultiply(testCase.Right);

		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
		EXPECT_FLOAT_EQ(result.w, testCase.Expected.w);
	}

	class Vector4fDivideComponentWiseTests : public testing::TestWithParam<Vector4fTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		Vector4fValues,
		Vector4fDivideComponentWiseTests,
		testing::Values
		(
			Vector4fTestCase
			{
				.Left = { 2.0f, 18.55f, 10.0f, 1.0f },
				.Right = { 1.0f, 3.5f, 2.0f, 1.0f },
				.Expected = { 2.0f, 5.3f, 5.0f, 1.0f }
			},
			Vector4fTestCase
			{
				.Left = { -55.65f, -189.4f, -88.6f, 0.0f },
				.Right = { -2.87f, -2.5f, -42.6f, 1.0f },
				.Expected = { 19.3902439f, 75.76f,  2.079812207f, 0.0f }
			},
			Vector4fTestCase
			{
				.Left = { 7.8f, -28.9f, 13.4f, 2.0f },
				.Right = { -16.47f, 13.25f, -33.0f, 1.0f },
				.Expected = { -0.473588342f, -2.181132075f, -0.4060606060f, 2.0f }
			}
		)
	);

	TEST_P(Vector4fDivideComponentWiseTests, ComponentWiseDivide_ShouldReturnQuotient_WhenDividingTwoVectors)
	{
		const Vector4fTestCase testCase = GetParam();

		const cocoa::math::Vector4f result = testCase.Left.ComponentWiseDivide(testCase.Right);

		EXPECT_FLOAT_EQ(result.x, testCase.Expected.x);
		EXPECT_FLOAT_EQ(result.y, testCase.Expected.y);
		EXPECT_FLOAT_EQ(result.z, testCase.Expected.z);
		EXPECT_FLOAT_EQ(result.w, testCase.Expected.w);
	}

	TEST(Vector4fTests, ComponentWiseDivide_ShouldAssert_WhenDividingByZeroXComponent)
	{
		const cocoa::math::Vector4f value{ 10.0f, 20.0f, 102.0f, 1.0f };
		const cocoa::math::Vector4f divisor{ 0.0f, 2.0f, 0.0f, 0.0f };

		EXPECT_DEBUG_DEATH(
			{
				const cocoa::math::Vector4f result = value.ComponentWiseDivide(divisor);
				(void)result;
			},
			"cannot divide by zero"
		);
	}

	TEST(Vector4fTests, Length_ShouldReturnMagnitude_WhenVectorHasComponent)
	{
		const cocoa::math::Vector4f sut(2.0f, 3.0f, 6.0f, 1.0f);

		const float result = sut.length();

		EXPECT_FLOAT_EQ(result, 7.0710678f);
	}

	TEST(Vector4fTests, LengthSquared_ShouldReturnSquaredMagnitude_WhenVectorHasComponents)
	{
		const cocoa::math::Vector4f sut{ 3.0f, 4.0f, 3.0f, 1.0f };

		const float result = sut.lengthSquared();

		EXPECT_FLOAT_EQ(result, 35.0f);
	}

	TEST(Vector4fTests, Dot_ShouldReturnDotProduct_WhenProvidingOtherVector)
	{
		const cocoa::math::Vector4f left{ 1.0f, 2.0f, 2.0f, 1.0f };
		const cocoa::math::Vector4f right{ 3.0f, 4.0f, 3.0f, 1.0f };

		const float result = left.dot(right);

		EXPECT_FLOAT_EQ(result, 18.0f);
	}

	TEST(Vector4fTests, Normalized_ShouldReturnUnitVector_WhenVectorIsNonZero)
	{
		const cocoa::math::Vector4f sut{ 2.0f, 3.0f, 4.0f, 1.0f };

		const cocoa::math::Vector4f result = sut.normalized();

		EXPECT_FLOAT_EQ(result.x, 0.36514837f);
		EXPECT_FLOAT_EQ(result.y, 0.54772252f);
		EXPECT_FLOAT_EQ(result.z, 0.73029673f);
		EXPECT_FLOAT_EQ(result.w, 0.182574186);
	}

	TEST(Vector4fTests, Normalized_ShouldAssert_WhenLengthIsZero)
	{
		const cocoa::math::Vector4f sut{ 0.f, 0.f, 0.0f, 0.0f };

		EXPECT_DEBUG_DEATH(
			{
				const cocoa::math::Vector4f result = sut.normalized();
				(void)result;
			},
			"cannot normalize a zero vector"
		);
	}
}
