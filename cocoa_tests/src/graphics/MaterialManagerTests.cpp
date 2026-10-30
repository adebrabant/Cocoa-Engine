#include <core/Color.hpp>
#include <graphics/GraphicsHandles.hpp>
#include <graphics/MaterialManager.hpp>

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

namespace CocoaTests::Graphics
{
	struct MaterialManagerBlendModeTestCase
	{
		std::string Input;
		cocoa::Graphics::BlendMode Expected;
	};

	TEST(MaterialManagerTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingValidId)
	{
		std::string materialId{ "test-material" };
		cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		cocoa::Core::Color tint;
		cocoa::Graphics::MaterialManager sut;

		cocoa::Graphics::MaterialHandle result = sut.Load(
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
		cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		cocoa::Core::Color tint;
		cocoa::Graphics::MaterialManager sut;

		cocoa::Graphics::MaterialHandle result1 = sut.Load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		cocoa::Graphics::MaterialHandle result2 = sut.Load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		EXPECT_EQ(result1.Id, result2.Id);
	}

	TEST(MaterialManagerTests, Load_ShouldReturnDifferentMaterialHandle_WhenProvidingDifferentMaterialId)
	{
		cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		cocoa::Core::Color tint;
		cocoa::Graphics::MaterialManager sut;

		cocoa::Graphics::MaterialHandle result1 = sut.Load(
			"test-material",
			shaderHandle,
			"opaque",
			tint
		);

		cocoa::Graphics::MaterialHandle result2 = sut.Load(
			"some-material",
			shaderHandle,
			"opaque",
			tint
		);

		EXPECT_NE(result1.Id, result2.Id);
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
				.Expected = cocoa::Graphics::BlendMode::Opaque
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "alpha",
				.Expected = cocoa::Graphics::BlendMode::Alpha
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "additive",
				.Expected = cocoa::Graphics::BlendMode::Additive
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "Subtractive",
				.Expected = cocoa::Graphics::BlendMode::Subtractive
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "reverse subtract",
				.Expected = cocoa::Graphics::BlendMode::ReverseSubtract
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "a",
				.Expected = cocoa::Graphics::BlendMode::Opaque
			}
		)
	);
	TEST_P(MaterialManagerBlendModeTests, Get_ShouldReturnMaterialExpectedBlendMode_WhenGivenInput)
	{
		const MaterialManagerBlendModeTestCase& testCase = GetParam();
		cocoa::Graphics::MaterialManager sut;

		cocoa::Graphics::MaterialHandle handle = sut.Load(
			"test-material",
			{ .Id = 1 },
			testCase.Input,
			{ 0.25f, 0.5f, 0.75f, 1.0f }
		);

		const cocoa::Graphics::Material& result = sut.Get(handle);

		EXPECT_EQ(testCase.Expected, result.Blend);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnMaterial_WhenProvidingValidHandle)
	{
		cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		cocoa::Core::Color tint{ 0.25f, 0.5f, 0.75f, 1.0f };
		cocoa::Graphics::MaterialManager sut;

		cocoa::Graphics::MaterialHandle handle = sut.Load(
			"test-material",
			shaderHandle,
			"alpha",
			tint
		);

		const cocoa::Graphics::Material& result = sut.Get(handle);

		EXPECT_EQ(shaderHandle.Id, result.Shader.Id);
		EXPECT_EQ(cocoa::Graphics::BlendMode::Alpha, result.Blend);
		EXPECT_FLOAT_EQ(tint.R, result.Tint.R);
		EXPECT_FLOAT_EQ(tint.G, result.Tint.G);
		EXPECT_FLOAT_EQ(tint.B, result.Tint.B);
		EXPECT_FLOAT_EQ(tint.A, result.Tint.A);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnSameMaterial_WhenProvidingSameHandle)
	{
		const std::string materialId{ "test-material" };
		cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		cocoa::Core::Color tint;
		cocoa::Graphics::MaterialManager sut;

		cocoa::Graphics::MaterialHandle handle = sut.Load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		const cocoa::Graphics::Material& result1 = sut.Get(handle);
		const cocoa::Graphics::Material& result2 = sut.Get(handle);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnDifferentMaterial_WhenProvidingDifferentHandle)
	{
		cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		cocoa::Core::Color tint;
		cocoa::Graphics::MaterialManager sut;
		cocoa::Graphics::MaterialHandle handle1 = sut.Load(
			"test-material",
			shaderHandle,
			"opaque",
			tint
		);
		cocoa::Graphics::MaterialHandle handle2 = sut.Load(
			"mock-material",
			shaderHandle,
			"opaque",
			tint
		);

		const cocoa::Graphics::Material& result1 = sut.Get(handle1);
		const cocoa::Graphics::Material& result2 = sut.Get(handle2);

		EXPECT_NE(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
	{
		const cocoa::Graphics::MaterialManager sut;
		constexpr cocoa::Graphics::MaterialHandle handle{ .Id = 9999 };

		EXPECT_THROW(
			{
				sut.Get(handle);
			},
			std::runtime_error
		);
	}
}
