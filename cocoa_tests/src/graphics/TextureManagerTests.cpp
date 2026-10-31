#include "stubs/graphics/StubGraphicsDevice.hpp"
#include "stubs/graphics/StubTexture2D.hpp"
#include <graphics/GraphicsHandles.hpp>
#include <graphics/TextureManager.hpp>
#include <graphics/TextureSpec.hpp>

#include <gtest/gtest.h>
#include <stdexcept>

namespace cocoa_tests::graphics
{
    TEST(TextureManagerTests, Load_ShouldReturnTextureHandle_WhenProvidingValidValues)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec;

        cocoa::graphics::TextureHandle result = sut.load(spec, "pixels");

        EXPECT_EQ(result.id, 1);
    }

    TEST(TextureManagerTests, Load_ShouldReturnSameTextureHandleId_WhenProvidingSameTextureSpecId)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec { .id = "default" };

        cocoa::graphics::TextureHandle result1 = sut.load(spec, "pixels");
        cocoa::graphics::TextureHandle result2 = sut.load(spec, "pixels");

        EXPECT_EQ(result1.id, result2.id);
    }

    TEST(TextureManagerTests, Load_ShouldReturnDifferentTextureHandleId_WhenProvidingDifferentTextureSpecId)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec1{ .id = "default" };
        cocoa::graphics::TextureSpec spec2{ .id = "non-default" };

        cocoa::graphics::TextureHandle result1 = sut.load(spec1, "pixels");
        cocoa::graphics::TextureHandle result2 = sut.load(spec2, "pixels");

        EXPECT_NE(result1.id, result2.id);
    }

    TEST(TextureManagerTests, Get_ShouldReturnTexture2D_WhenProvidingValidHandle)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec{ .id = "default" };

        cocoa::graphics::TextureHandle handle = sut.load(spec, "default");
        const cocoa::graphics::Texture2D& texture = sut.get(handle);

        EXPECT_NE(&texture, nullptr);
    }

    TEST(TextureManagerTests, Get_ShouldReturnDifferentTexture_WhenProvidingDifferentHandles)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec1{ .id = "default" };
        cocoa::graphics::TextureSpec spec2{ .id = "non-default" };

        cocoa::graphics::TextureHandle handle1 = sut.load(spec1, "pixels");
        cocoa::graphics::TextureHandle handle2 = sut.load(spec2, "pixels");
        const cocoa::graphics::Texture2D& texture1 = sut.get(handle1);
        const cocoa::graphics::Texture2D& texture2 = sut.get(handle2);

        EXPECT_NE(&texture1, &texture2);
    }

    TEST(TextureManagerTests, Get_ShouldReturnSameTexture_WhenProvidingSameHandle)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec{ .id = "default" };

        cocoa::graphics::TextureHandle handle = sut.load(spec, "pixels");
        const cocoa::graphics::Texture2D& texture1 = sut.get(handle);
        const cocoa::graphics::Texture2D& texture2 = sut.get(handle);

        EXPECT_EQ(&texture1, &texture2);
    }

    TEST(TextureManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);

        cocoa::graphics::TextureHandle handle{ .id = 9999 };

        EXPECT_THROW(
            {
                sut.get(handle);
            },
            std::runtime_error
        );
    }

    TEST(TextureManagerTests, TryGetHandle_ShouldReturnTrueAndOutHandle_WhenIdExists)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec{ .id = "default" };
        cocoa::graphics::TextureHandle expectedHandle = sut.load(spec, "pixels");

        cocoa::graphics::TextureHandle outHandle;
        bool result = sut.tryGetHandle(spec.id, outHandle);

        EXPECT_TRUE(result);
        EXPECT_EQ(outHandle.id, expectedHandle.id);
    }

    TEST(TextureManagerTests, TryGetHandle_ShouldReturnFalseAndOutHandle_WhenIdDoesNotExist)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec{ .id = "default" };
        sut.load(spec, "pixels");

        cocoa::graphics::TextureHandle outHandle;
        bool result = sut.tryGetHandle("badId", outHandle);

        EXPECT_FALSE(result);
        EXPECT_EQ(outHandle.id, 0);
    }
}
