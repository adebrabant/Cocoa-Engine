#include <Core/Color.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/GraphicsHandles.hpp>

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

namespace CocoaTests::Graphics
{
	struct MaterialManagerBlendModeTestCase
	{
		std::string Input;
		Cocoa::Graphics::BlendMode Expected;
	};

	TEST(MaterialManagerTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingValidId)
	{
		std::string materialId{ "test-material" };
		Cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Cocoa::Core::Color tint;
		Cocoa::Graphics::MaterialManager sut;

		Cocoa::Graphics::MaterialHandle result = sut.Load(
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
		Cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Cocoa::Core::Color tint;
		Cocoa::Graphics::MaterialManager sut;

		Cocoa::Graphics::MaterialHandle result1 = sut.Load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		Cocoa::Graphics::MaterialHandle result2 = sut.Load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		EXPECT_EQ(result1.Id, result2.Id);
	}

	TEST(MaterialManagerTests, Load_ShouldReturnDifferentMaterialHandle_WhenProvidingDifferentMaterialId)
	{
		Cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Cocoa::Core::Color tint;
		Cocoa::Graphics::MaterialManager sut;

		Cocoa::Graphics::MaterialHandle result1 = sut.Load(
			"test-material",
			shaderHandle,
			"opaque",
			tint
		);

		Cocoa::Graphics::MaterialHandle result2 = sut.Load(
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
				.Expected = Cocoa::Graphics::BlendMode::Opaque
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "alpha",
				.Expected = Cocoa::Graphics::BlendMode::Alpha
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "additive",
				.Expected = Cocoa::Graphics::BlendMode::Additive
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "Subtractive",
				.Expected = Cocoa::Graphics::BlendMode::Subtractive
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "reverse subtract",
				.Expected = Cocoa::Graphics::BlendMode::ReverseSubtract
			},
			MaterialManagerBlendModeTestCase
			{
				.Input = "a",
				.Expected = Cocoa::Graphics::BlendMode::Opaque
			}
		)
	);
	TEST_P(MaterialManagerBlendModeTests, Get_ShouldReturnMaterialExpectedBlendMode_WhenGivenInput)
	{
		const MaterialManagerBlendModeTestCase& testCase = GetParam();
		Cocoa::Graphics::MaterialManager sut;

		Cocoa::Graphics::MaterialHandle handle = sut.Load(
			"test-material",
			{ .Id = 1 },
			testCase.Input,
			{ 0.25f, 0.5f, 0.75f, 1.0f }
		);

		const Cocoa::Graphics::Material& result = sut.Get(handle);

		EXPECT_EQ(testCase.Expected, result.Blend);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnMaterial_WhenProvidingValidHandle)
	{
		Cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Cocoa::Core::Color tint{ 0.25f, 0.5f, 0.75f, 1.0f };
		Cocoa::Graphics::MaterialManager sut;

		Cocoa::Graphics::MaterialHandle handle = sut.Load(
			"test-material",
			shaderHandle,
			"alpha",
			tint
		);

		const Cocoa::Graphics::Material& result = sut.Get(handle);

		EXPECT_EQ(shaderHandle.Id, result.Shader.Id);
		EXPECT_EQ(Cocoa::Graphics::BlendMode::Alpha, result.Blend);
		EXPECT_FLOAT_EQ(tint.R, result.Tint.R);
		EXPECT_FLOAT_EQ(tint.G, result.Tint.G);
		EXPECT_FLOAT_EQ(tint.B, result.Tint.B);
		EXPECT_FLOAT_EQ(tint.A, result.Tint.A);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnSameMaterial_WhenProvidingSameHandle)
	{
		const std::string materialId{ "test-material" };
		Cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Cocoa::Core::Color tint;
		Cocoa::Graphics::MaterialManager sut;

		Cocoa::Graphics::MaterialHandle handle = sut.Load(
			materialId,
			shaderHandle,
			"opaque",
			tint
		);

		const Cocoa::Graphics::Material& result1 = sut.Get(handle);
		const Cocoa::Graphics::Material& result2 = sut.Get(handle);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnDifferentMaterial_WhenProvidingDifferentHandle)
	{
		Cocoa::Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Cocoa::Core::Color tint;
		Cocoa::Graphics::MaterialManager sut;
		Cocoa::Graphics::MaterialHandle handle1 = sut.Load(
			"test-material",
			shaderHandle,
			"opaque",
			tint
		);
		Cocoa::Graphics::MaterialHandle handle2 = sut.Load(
			"mock-material",
			shaderHandle,
			"opaque",
			tint
		);

		const Cocoa::Graphics::Material& result1 = sut.Get(handle1);
		const Cocoa::Graphics::Material& result2 = sut.Get(handle2);

		EXPECT_NE(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
	{
		const Cocoa::Graphics::MaterialManager sut;
		constexpr Cocoa::Graphics::MaterialHandle handle{ .Id = 9999 };

		EXPECT_THROW(
			{
				sut.Get(handle);
			},
			std::runtime_error
		);
	}
}