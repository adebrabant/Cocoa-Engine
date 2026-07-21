#include <Core/Color.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/GraphicsHandles.hpp>

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

namespace Cocoa::Graphics::Tests
{
	TEST(MaterialManagerTests, LoadMaterial_ShouldReturnMaterialHandle_WhenProvidingValidId)
	{
		std::string materialId{ "test-material" };
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Graphics::TextureHandle textureHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle result = sut.Load(
			materialId, 
			shaderHandle, 
			textureHandle,
			tint
		);

		EXPECT_NE(&result, nullptr);
	}

	TEST(MaterialManagerTests, Load_ShouldReturnSameMaterialHandle_WhenProvidingSameMaterialId)
	{
		std::string materialId{ "test-material" };
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Graphics::TextureHandle textureHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle result1 = sut.Load(
			materialId,
			shaderHandle,
			textureHandle,
			tint
		);

		Graphics::MaterialHandle result2 = sut.Load(
			materialId,
			shaderHandle,
			textureHandle,
			tint
		);

		EXPECT_EQ(result1.Id, result2.Id);
	}

	TEST(MaterialManagerTests, Load_ShouldReturnDifferentMaterialHandle_WhenProvidingDifferentMaterialId)
	{
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Graphics::TextureHandle textureHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle result1 = sut.Load(
			"test-material",
			shaderHandle,
			textureHandle,
			tint
		);

		Graphics::MaterialHandle result2 = sut.Load(
			"some-material",
			shaderHandle,
			textureHandle,
			tint
		);

		EXPECT_NE(result1.Id, result2.Id);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnMaterial_WhenProvidingValidHandle)
	{
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Graphics::TextureHandle textureHandle{ .Id = 1 };
		Core::Color tint{ 0.25f, 0.5f, 0.75f, 1.0f };
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle handle = sut.Load(
			"test-material",
			shaderHandle,
			textureHandle,
			tint
		);

		const Graphics::Material& result = sut.Get(handle);

		EXPECT_NE(&result, nullptr);
		EXPECT_EQ(result.ShaderId.Id, shaderHandle.Id);
		EXPECT_EQ(result.TextureId.Id, textureHandle.Id);
		EXPECT_FLOAT_EQ(result.Tint.R, tint.R);
		EXPECT_FLOAT_EQ(result.Tint.G, tint.G);
		EXPECT_FLOAT_EQ(result.Tint.B, tint.B);
		EXPECT_FLOAT_EQ(result.Tint.A, tint.A);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnSameMaterial_WhenProvidingSameHandle)
	{
		const std::string materialId{ "test-material" };
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Graphics::TextureHandle textureHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;

		Graphics::MaterialHandle handle = sut.Load(
			materialId,
			shaderHandle,
			textureHandle,
			tint
		);

		const Graphics::Material& result1 = sut.Get(handle);
		const Graphics::Material& result2 = sut.Get(handle);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldReturnDifferentMaterial_WhenProvidingDifferentHandle)
	{
		Graphics::ShaderHandle shaderHandle{ .Id = 1 };
		Graphics::TextureHandle textureHandle{ .Id = 1 };
		Core::Color tint;
		Graphics::MaterialManager sut;
		Graphics::MaterialHandle handle1 = sut.Load(
			"test-material",
			shaderHandle,
			textureHandle,
			tint
		);
		Graphics::MaterialHandle handle2 = sut.Load(
			"mock-material",
			shaderHandle,
			textureHandle,
			tint
		);

		const Graphics::Material& result1 = sut.Get(handle1);
		const Graphics::Material& result2 = sut.Get(handle2);

		EXPECT_NE(&result1, &result2);
	}

	TEST(MaterialManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
	{
		Graphics::MaterialManager sut;
		MaterialHandle handle{ .Id = 9999 };

		EXPECT_THROW(
			{
				sut.Get(handle);
			},
			std::runtime_error
		);
	}
}