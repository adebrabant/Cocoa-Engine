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

        cocoa::graphics::TextureHandle result = sut.Load(spec, "pixels");

        EXPECT_EQ(result.Id, 1);
    }

    TEST(TextureManagerTests, Load_ShouldReturnSameTextureHandleId_WhenProvidingSameTextureSpecId)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec { .Id = "default" };

        cocoa::graphics::TextureHandle result1 = sut.Load(spec, "pixels");
        cocoa::graphics::TextureHandle result2 = sut.Load(spec, "pixels");

        EXPECT_EQ(result1.Id, result2.Id);
    }

    TEST(TextureManagerTests, Load_ShouldReturnDifferentTextureHandleId_WhenProvidingDifferentTextureSpecId)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec1{ .Id = "default" };
        cocoa::graphics::TextureSpec spec2{ .Id = "non-default" };

        cocoa::graphics::TextureHandle result1 = sut.Load(spec1, "pixels");
        cocoa::graphics::TextureHandle result2 = sut.Load(spec2, "pixels");

        EXPECT_NE(result1.Id, result2.Id);
    }

    TEST(TextureManagerTests, Get_ShouldReturnTexture2D_WhenProvidingValidHandle)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec{ .Id = "default" };

        cocoa::graphics::TextureHandle handle = sut.Load(spec, "default");
        const cocoa::graphics::Texture2D& texture = sut.Get(handle);

        EXPECT_NE(&texture, nullptr);
    }

    TEST(TextureManagerTests, Get_ShouldReturnDifferentTexture_WhenProvidingDifferentHandles)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec1{ .Id = "default" };
        cocoa::graphics::TextureSpec spec2{ .Id = "non-default" };

        cocoa::graphics::TextureHandle handle1 = sut.Load(spec1, "pixels");
        cocoa::graphics::TextureHandle handle2 = sut.Load(spec2, "pixels");
        const cocoa::graphics::Texture2D& texture1 = sut.Get(handle1);
        const cocoa::graphics::Texture2D& texture2 = sut.Get(handle2);

        EXPECT_NE(&texture1, &texture2);
    }

    TEST(TextureManagerTests, Get_ShouldReturnSameTexture_WhenProvidingSameHandle)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec{ .Id = "default" };

        cocoa::graphics::TextureHandle handle = sut.Load(spec, "pixels");
        const cocoa::graphics::Texture2D& texture1 = sut.Get(handle);
        const cocoa::graphics::Texture2D& texture2 = sut.Get(handle);

        EXPECT_EQ(&texture1, &texture2);
    }

    TEST(TextureManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);

        cocoa::graphics::TextureHandle handle{ .Id = 9999 };

        EXPECT_THROW(
            {
                sut.Get(handle);
            },
            std::runtime_error
        );
    }

    TEST(TextureManagerTests, TryGetHandle_ShouldReturnTrueAndOutHandle_WhenIdExists)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec{ .Id = "default" };
        cocoa::graphics::TextureHandle expectedHandle = sut.Load(spec, "pixels");

        cocoa::graphics::TextureHandle outHandle;
        bool result = sut.TryGetHandle(spec.Id, outHandle);

        EXPECT_TRUE(result);
        EXPECT_EQ(outHandle.Id, expectedHandle.Id);
    }

    TEST(TextureManagerTests, TryGetHandle_ShouldReturnFalseAndOutHandle_WhenIdDoesNotExist)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::TextureManager sut(stubGraphicsDevice);
        cocoa::graphics::TextureSpec spec{ .Id = "default" };
        sut.Load(spec, "pixels");

        cocoa::graphics::TextureHandle outHandle;
        bool result = sut.TryGetHandle("badId", outHandle);

        EXPECT_FALSE(result);
        EXPECT_EQ(outHandle.Id, 0);
    }
}
