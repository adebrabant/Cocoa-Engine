#include <Graphics/SpriteManager.hpp>
#include <Graphics/GraphicsHandles.hpp>
#include <gtest/gtest.h>

namespace Cocoa::Graphics::Tests
{
	TEST(SpriteManagerTests, Load_ShouldReturnSpriteHandle_WhenProvidingValidId)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr Graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr Math::Vector2f minUV(0, 0.5);
		constexpr Math::Vector2f maxUV(1, 1.5);
		Graphics::SpriteManager sut;

		Graphics::SpriteHandle result = sut.Load(
			spriteId,
			textureHandle,
			minUV,
			maxUV
		);

		EXPECT_NE(&result, nullptr);
	}

	TEST(SpriteManagerTests, Load_ShouldReturnSameSpriteHandle_WhenProvidingSameSpriteId)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr Graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr Math::Vector2f minUV(0, 0.5);
		constexpr Math::Vector2f maxUV(1, 1.5);
		Graphics::SpriteManager sut;

		const Graphics::SpriteHandle result1 = sut.Load(
			spriteId,
			textureHandle,
			minUV,
			maxUV
		);

		const Graphics::SpriteHandle result2 = sut.Load(
			spriteId,
			textureHandle,
			minUV,
			maxUV
		);

		EXPECT_EQ(result1.Id, result2.Id);
	}

	TEST(SpriteManagerTests, Load_ShouldReturnDifferentSpriteHandle_WhenProvidingDifferentSpriteId)
	{
		constexpr Graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr Math::Vector2f minUV(0, 0.5);
		constexpr Math::Vector2f maxUV(1, 1.5);
		Graphics::SpriteManager sut;

		const Graphics::SpriteHandle result1 = sut.Load(
			"test-sprite",
			textureHandle,
			minUV,
			maxUV
		);

		const Graphics::SpriteHandle result2 = sut.Load(
			"some-sprite",
			textureHandle,
			minUV,
			maxUV
		);

		EXPECT_NE(result1.Id, result2.Id);
	}

	TEST(SpriteManagerTests, Get_ShouldReturnSprite_WhenProvidingValidHandle)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr Graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr Math::Vector2f minUV(0, 0.5);
		constexpr Math::Vector2f maxUV(1, 1.5);
		Graphics::SpriteManager sut;

		const Graphics::SpriteHandle handle = sut.Load(
			spriteId,
			textureHandle,
			minUV,
			maxUV
		);

		const Graphics::Sprite& result = sut.Get(handle);

		EXPECT_NE(&result, nullptr);
		EXPECT_EQ(result.Id, spriteId);
		EXPECT_EQ(result.Texture.Id, textureHandle.Id);
		EXPECT_FLOAT_EQ(result.MinUV.X, minUV.X);
		EXPECT_FLOAT_EQ(result.MinUV.Y, minUV.Y);
		EXPECT_FLOAT_EQ(result.MaxUV.X, maxUV.X);
		EXPECT_FLOAT_EQ(result.MaxUV.Y, maxUV.Y);
	}

	TEST(SpriteManagerTests, Get_ShouldReturnSameSprite_WhenProvidingSameHandle)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr Graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr Math::Vector2f minUV(0, 0.5);
		constexpr Math::Vector2f maxUV(1, 1.5);
		Graphics::SpriteManager sut;

		const Graphics::SpriteHandle handle = sut.Load(
			spriteId,
			textureHandle,
			minUV,
			maxUV
		);

		const Graphics::Sprite& result1 = sut.Get(handle);
		const Graphics::Sprite& result2 = sut.Get(handle);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(SpriteManagerTests, Get_ShouldReturnDifferentSprite_WhenProvidingDifferentHandle)
	{
		constexpr Graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr Math::Vector2f minUV(0, 0.5);
		constexpr Math::Vector2f maxUV(1, 1.5);
		Graphics::SpriteManager sut;
		const Graphics::SpriteHandle handle1 = sut.Load(
			"test-sprite",
			textureHandle,
			minUV,
			maxUV
		);
		const Graphics::SpriteHandle handle2 = sut.Load(
			"mock-sprite",
			textureHandle,
			minUV,
			maxUV
		);

		const Graphics::Sprite& result1 = sut.Get(handle1);
		const Graphics::Sprite& result2 = sut.Get(handle2);

		EXPECT_NE(&result1, &result2);
	}

	TEST(SpriteManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
	{
		Graphics::SpriteManager sut;
		constexpr SpriteHandle handle{ .Id = 9999 };

		EXPECT_THROW(
			{
				sut.Get(handle);
			},
			std::runtime_error
		);
	}
}
