#include <graphics/GraphicsHandles.hpp>
#include <graphics/SpriteManager.hpp>
#include <gtest/gtest.h>

namespace cocoa_tests::graphics
{
	TEST(SpriteManagerTests, Load_ShouldReturnSpriteHandle_WhenProvidingValidId)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr cocoa::graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;

		cocoa::graphics::SpriteHandle result = sut.Load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		EXPECT_EQ(1, result.Id);
	}

	TEST(SpriteManagerTests, Load_ShouldReturnSameSpriteHandle_WhenProvidingSameSpriteId)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr cocoa::graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;

		const cocoa::graphics::SpriteHandle result1 = sut.Load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::SpriteHandle result2 = sut.Load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		EXPECT_EQ(result1.Id, result2.Id);
	}

	TEST(SpriteManagerTests, Load_ShouldReturnDifferentSpriteHandle_WhenProvidingDifferentSpriteId)
	{
		constexpr cocoa::graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;

		const cocoa::graphics::SpriteHandle result1 = sut.Load(
			"test-sprite",
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::SpriteHandle result2 = sut.Load(
			"some-sprite",
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		EXPECT_NE(result1.Id, result2.Id);
	}

	TEST(SpriteManagerTests, Get_ShouldReturnSprite_WhenProvidingValidHandle)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr cocoa::graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr cocoa::math::Vector2f minPixel(250.0f, 400.0f);
		constexpr cocoa::math::Vector2f maxPixel(500.0f, 800.0f);
		constexpr cocoa::math::Vector2f textureSize(1000.0f, 800.0f);
		cocoa::graphics::SpriteManager sut;

		const cocoa::graphics::SpriteHandle handle = sut.Load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::Sprite& result = sut.Get(handle);

		EXPECT_EQ(spriteId, result.Id);
		EXPECT_EQ(textureHandle.Id, result.Texture.Id);
		EXPECT_FLOAT_EQ(0.25f, result.MinUV.X);
		EXPECT_FLOAT_EQ(0.5f, result.MinUV.Y);
		EXPECT_FLOAT_EQ(0.5f, result.MaxUV.X);
		EXPECT_FLOAT_EQ(1.0f, result.MaxUV.Y);
	}

	TEST(SpriteManagerTests, Get_ShouldReturnSameSprite_WhenProvidingSameHandle)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr cocoa::graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;

		const cocoa::graphics::SpriteHandle handle = sut.Load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::Sprite& result1 = sut.Get(handle);
		const cocoa::graphics::Sprite& result2 = sut.Get(handle);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(SpriteManagerTests, Get_ShouldReturnDifferentSprite_WhenProvidingDifferentHandle)
	{
		constexpr cocoa::graphics::TextureHandle textureHandle{ .Id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;
		const cocoa::graphics::SpriteHandle handle1 = sut.Load(
			"test-sprite",
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);
		const cocoa::graphics::SpriteHandle handle2 = sut.Load(
			"mock-sprite",
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::Sprite& result1 = sut.Get(handle1);
		const cocoa::graphics::Sprite& result2 = sut.Get(handle2);

		EXPECT_NE(&result1, &result2);
	}

	TEST(SpriteManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
	{
		const cocoa::graphics::SpriteManager sut;
		constexpr cocoa::graphics::SpriteHandle handle{ .Id = 9999 };

		EXPECT_THROW(
			{
				sut.Get(handle);
			},
			std::runtime_error
		);
	}
}
