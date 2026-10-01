#include <Core/Color.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/GraphicsHandles.hpp>

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

namespace Cocoa::Graphics::Tests
{
	struct MaterialManagerBlendModeTestCase
	{
		std::string Input;
		BlendMode Expected;
	};

	TEST(MaterialManagerTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingValidId)
	{
		std::string materialId{ "test-material" };
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle result = sut.Load(
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
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle result1 = sut.Load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		Graphics::MaterialHandle result2 = sut.Load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		EXPECT_EQ(result1.Id, result2.Id);
	}

	TEST(MaterialManagerTests, Load_ShouldReturnDifferentMaterialHandle_WhenProvidingDifferentMaterialId)
	{
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle result1 = sut.Load(
			"test-material",
			shaderHandle,
			"opaque",
			tint
		);

		Graphics::MaterialHandle result2 = sut.Load(
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
				.Expected = BlendMode::Opaque
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "alpha",
				.Expected = BlendMode::Alpha
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "additive",
				.Expected = BlendMode::Additive
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "Subtractive",
				.Expected = BlendMode::Subtractive
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "reverse subtract",
				.Expected = BlendMode::ReverseSubtract
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "a",
				.Expected = BlendMode::Opaque
			}
		)
	);
	TEST_P(MaterialManagerBlendModeTests, Get_ShouldReturnMaterialExpectedBlendMode_WhenGivenInput)
	{
		const MaterialManagerBlendModeTestCase& testCase = GetParam();
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle handle = sut.Load(
			"test-material",
			{ .Id = 1 },
			testCase.Input,
			{ 0.25f, 0.5f, 0.75f, 1.0f }
		);

		const Graphics::Material& result = sut.Get(handle);

		EXPECT_EQ(testCase.Expected, result.Blend);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnMaterial_WhenProvidingValidHandle)
	{
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Core::Color tint{ 0.25f, 0.5f, 0.75f, 1.0f };
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle handle = sut.Load(
			"test-material",
			shaderHandle,
			"alpha",
			tint
		);

		const Graphics::Material& result = sut.Get(handle);

		EXPECT_EQ(shaderHandle.Id, result.Shader.Id);
		EXPECT_EQ(BlendMode::Alpha, result.Blend);
		EXPECT_FLOAT_EQ(tint.R, result.Tint.R);
		EXPECT_FLOAT_EQ(tint.G, result.Tint.G);
		EXPECT_FLOAT_EQ(tint.B, result.Tint.B);
		EXPECT_FLOAT_EQ(tint.A, result.Tint.A);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnSameMaterial_WhenProvidingSameHandle)
	{
		const std::string materialId{ "test-material" };
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle handle = sut.Load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		const Graphics::Material& result1 = sut.Get(handle);
		const Graphics::Material& result2 = sut.Get(handle);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnDifferentMaterial_WhenProvidingDifferentHandle)
	{
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;
		Graphics::MaterialHandle handle1 = sut.Load(
			"test-material",
			shaderHandle,
			"opaque",
			tint
		);
		Graphics::MaterialHandle handle2 = sut.Load(
			"mock-material",
			shaderHandle,
			"opaque",
			tint
		);

		const Graphics::Material& result1 = sut.Get(handle1);
		const Graphics::Material& result2 = sut.Get(handle2);

		EXPECT_NE(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
	{
		const Graphics::MaterialManager sut;
		constexpr MaterialHandle handle{ .Id = 9999 };

		EXPECT_THROW(
			{
				sut.Get(handle);
			},
			std::runtime_error
		);
	}
}