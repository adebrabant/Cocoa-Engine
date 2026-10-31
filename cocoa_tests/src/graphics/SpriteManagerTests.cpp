#include <graphics/GraphicsHandles.hpp>
#include <graphics/SpriteManager.hpp>
#include <gtest/gtest.h>

namespace cocoa_tests::graphics
{
	TEST(SpriteManagerTests, Load_ShouldReturnSpriteHandle_WhenProvidingValidId)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr cocoa::graphics::TextureHandle textureHandle{ .id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;

		cocoa::graphics::SpriteHandle result = sut.load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		EXPECT_EQ(1, result.id);
	}

	TEST(SpriteManagerTests, Load_ShouldReturnSameSpriteHandle_WhenProvidingSameSpriteId)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr cocoa::graphics::TextureHandle textureHandle{ .id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;

		const cocoa::graphics::SpriteHandle result1 = sut.load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::SpriteHandle result2 = sut.load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		EXPECT_EQ(result1.id, result2.id);
	}

	TEST(SpriteManagerTests, Load_ShouldReturnDifferentSpriteHandle_WhenProvidingDifferentSpriteId)
	{
		constexpr cocoa::graphics::TextureHandle textureHandle{ .id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;

		const cocoa::graphics::SpriteHandle result1 = sut.load(
			"test-sprite",
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::SpriteHandle result2 = sut.load(
			"some-sprite",
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		EXPECT_NE(result1.id, result2.id);
	}

	TEST(SpriteManagerTests, Get_ShouldReturnSprite_WhenProvidingValidHandle)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr cocoa::graphics::TextureHandle textureHandle{ .id = 1 };
		constexpr cocoa::math::Vector2f minPixel(250.0f, 400.0f);
		constexpr cocoa::math::Vector2f maxPixel(500.0f, 800.0f);
		constexpr cocoa::math::Vector2f textureSize(1000.0f, 800.0f);
		cocoa::graphics::SpriteManager sut;

		const cocoa::graphics::SpriteHandle handle = sut.load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::Sprite& result = sut.get(handle);

		EXPECT_EQ(spriteId, result.id);
		EXPECT_EQ(textureHandle.id, result.textureHandle.id);
		EXPECT_FLOAT_EQ(0.25f, result.minUV.x);
		EXPECT_FLOAT_EQ(0.5f, result.minUV.y);
		EXPECT_FLOAT_EQ(0.5f, result.maxUV.x);
		EXPECT_FLOAT_EQ(1.0f, result.maxUV.y);
	}

	TEST(SpriteManagerTests, Get_ShouldReturnSameSprite_WhenProvidingSameHandle)
	{
		const std::string spriteId{ "test-sprite" };
		constexpr cocoa::graphics::TextureHandle textureHandle{ .id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;

		const cocoa::graphics::SpriteHandle handle = sut.load(
			spriteId,
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::Sprite& result1 = sut.get(handle);
		const cocoa::graphics::Sprite& result2 = sut.get(handle);

		EXPECT_EQ(&result1, &result2);
	}

	TEST(SpriteManagerTests, Get_ShouldReturnDifferentSprite_WhenProvidingDifferentHandle)
	{
		constexpr cocoa::graphics::TextureHandle textureHandle{ .id = 1 };
		constexpr cocoa::math::Vector2f minPixel(0.0f, 0.0f);
		constexpr cocoa::math::Vector2f maxPixel(256.0f, 256.0f);
		constexpr cocoa::math::Vector2f textureSize(256.0f, 256.0f);
		cocoa::graphics::SpriteManager sut;
		const cocoa::graphics::SpriteHandle handle1 = sut.load(
			"test-sprite",
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);
		const cocoa::graphics::SpriteHandle handle2 = sut.load(
			"mock-sprite",
			textureHandle,
			minPixel,
			maxPixel,
			textureSize
		);

		const cocoa::graphics::Sprite& result1 = sut.get(handle1);
		const cocoa::graphics::Sprite& result2 = sut.get(handle2);

		EXPECT_NE(&result1, &result2);
	}

	TEST(SpriteManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
	{
		const cocoa::graphics::SpriteManager sut;
		constexpr cocoa::graphics::SpriteHandle handle{ .id = 9999 };

		EXPECT_THROW(
			{
				sut.get(handle);
			},
			std::runtime_error
		);
	}
}
