#include <core/Color.hpp>
#include <graphics/GraphicsHandles.hpp>
#include <graphics/MaterialManager.hpp>

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

namespace cocoa_tests::graphics
{
	struct MaterialManagerBlendModeTestCase
	{
		std::string Input;
		cocoa::graphics::BlendMode Expected;
	};

	TEST(MaterialManagerTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingValidId)
	{
		std::string materialId{ "test-material" };
		cocoa::graphics::ShaderHandle shaderHandle{ .id = 1 };
		cocoa::core::Color tint;
		cocoa::graphics::MaterialManager sut;

		cocoa::graphics::MaterialHandle result = sut.load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		EXPECT_NE(nullptr, &result);
	}

	TEST(MaterialManagerTests, Load_ShouldReturnSameMaterialHandle_WhenProvidingSameMaterialId)
	{
		std::string materialId{ "test-material" };
		cocoa::graphics::ShaderHandle shaderHandle{ .id = 1 };
		cocoa::core::Color tint;
		cocoa::graphics::MaterialManager sut;

		cocoa::graphics::MaterialHandle result1 = sut.load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		cocoa::graphics::MaterialHandle result2 = sut.load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		EXPECT_EQ(result1.id, result2.id);
	}

	TEST(MaterialManagerTests, Load_ShouldReturnDifferentMaterialHandle_WhenProvidingDifferentMaterialId)
	{
		cocoa::graphics::ShaderHandle shaderHandle{ .id = 1 };
		cocoa::core::Color tint;
		cocoa::graphics::MaterialManager sut;

		cocoa::graphics::MaterialHandle result1 = sut.load(
			"test-material",
			shaderHandle,
			"opaque",
			tint
		);

		cocoa::graphics::MaterialHandle result2 = sut.load(
			"some-material",
			shaderHandle,
			"opaque",
			tint
		);

		EXPECT_NE(result1.id, result2.id);
	}

	class MaterialManagerBlendModeTests : public testing::TestWithParam<MaterialManagerBlendModeTestCase> {};
	INSTANTIATE_TEST_SUITE_P(
		MaterialManagerValues,
		MaterialManagerBlendModeTests,
		testing::Values
		(
			MaterialManagerBlendModeTestCase
			{
				.Input = " opaque ",
				.Expected = cocoa::graphics::BlendMode::Opaque
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "alpha",
				.Expected = cocoa::graphics::BlendMode::Alpha
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "additive",
				.Expected = cocoa::graphics::BlendMode::Additive
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "Subtractive",
				.Expected = cocoa::graphics::BlendMode::Subtractive
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "reverse subtract",
				.Expected = cocoa::graphics::BlendMode::ReverseSubtract
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "a",
				.Expected = cocoa::graphics::BlendMode::Opaque
			}
		)
	);
	TEST_P(MaterialManagerBlendModeTests, Get_ShouldReturnMaterialExpectedBlendMode_WhenGivenInput)
	{
		const MaterialManagerBlendModeTestCase& testCase = GetParam();
		cocoa::graphics::MaterialManager sut;

		cocoa::graphics::MaterialHandle handle = sut.load(
			"test-material",
			{ .id = 1 },
			testCase.Input,
			{ 0.25f, 0.5f, 0.75f, 1.0f }
		);

		const cocoa::graphics::Material& result = sut.get(handle);

		EXPECT_EQ(testCase.Expected, result.blendMode);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnMaterial_WhenProvidingValidHandle)
	{
		cocoa::graphics::ShaderHandle shaderHandle{ .id = 1 };
		cocoa::core::Color tint{ 0.25f, 0.5f, 0.75f, 1.0f };
		cocoa::graphics::MaterialManager sut;

		cocoa::graphics::MaterialHandle handle = sut.load(
			"test-material",
			shaderHandle,
			"alpha",
			tint
		);

		const cocoa::graphics::Material& result = sut.get(handle);

		EXPECT_EQ(shaderHandle.id, result.shaderHandle.id);
		EXPECT_EQ(cocoa::graphics::BlendMode::Alpha, result.blendMode);
		EXPECT_FLOAT_EQ(tint.r, result.tint.r);
		EXPECT_FLOAT_EQ(tint.g, result.tint.g);
		EXPECT_FLOAT_EQ(tint.b, result.tint.b);
		EXPECT_FLOAT_EQ(tint.a, result.tint.a);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnSameMaterial_WhenProvidingSameHandle)
	{
		const std::string materialId{ "test-material" };
		cocoa::graphics::ShaderHandle shaderHandle{ .id = 1 };
		cocoa::core::Color tint;
		cocoa::graphics::MaterialManager sut;

		cocoa::graphics::MaterialHandle handle = sut.load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		const cocoa::graphics::Material& result1 = sut.get(handle);
		const cocoa::graphics::Material& result2 = sut.get(handle);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnDifferentMaterial_WhenProvidingDifferentHandle)
	{
		cocoa::graphics::ShaderHandle shaderHandle{ .id = 1 };
		cocoa::core::Color tint;
		cocoa::graphics::MaterialManager sut;
		cocoa::graphics::MaterialHandle handle1 = sut.load(
			"test-material",
			shaderHandle,
			"opaque",
			tint
		);
		cocoa::graphics::MaterialHandle handle2 = sut.load(
			"mock-material",
			shaderHandle,
			"opaque",
			tint
		);

		const cocoa::graphics::Material& result1 = sut.get(handle1);
		const cocoa::graphics::Material& result2 = sut.get(handle2);

		EXPECT_NE(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
	{
		const cocoa::graphics::MaterialManager sut;
		constexpr cocoa::graphics::MaterialHandle handle{ .id = 9999 };

		EXPECT_THROW(
			{
				sut.get(handle);
			},
			std::runtime_error
		);
	}
}
