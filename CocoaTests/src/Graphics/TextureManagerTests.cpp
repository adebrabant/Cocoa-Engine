#include "Stubs/Graphics/StubGraphicsDevice.hpp"
#include "Stubs/Graphics/StubTexture2D.hpp"
#include <Graphics/TextureManager.hpp>
#include <Graphics/TextureSpec.hpp>
#include <Graphics/GraphicsHandles.hpp>

#include <gtest/gtest.h>
#include <stdexcept>

namespace CocoaTests::Graphics
{
    TEST(TextureManagerTests, Load_ShouldReturnTextureHandle_WhenProvidingValidValues)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::TextureManager sut(stubGraphicsDevice);
        Cocoa::Graphics::TextureSpec spec;

        Cocoa::Graphics::TextureHandle result = sut.Load(spec, "pixels");

        EXPECT_EQ(result.Id, 1);
    }

    TEST(TextureManagerTests, Load_ShouldReturnSameTextureHandleId_WhenProvidingSameTextureSpecId)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::TextureManager sut(stubGraphicsDevice);
        Cocoa::Graphics::TextureSpec spec { .Id = "default" };

        Cocoa::Graphics::TextureHandle result1 = sut.Load(spec, "pixels");
        Cocoa::Graphics::TextureHandle result2 = sut.Load(spec, "pixels");

        EXPECT_EQ(result1.Id, result2.Id);
    }

    TEST(TextureManagerTests, Load_ShouldReturnDifferentTextureHandleId_WhenProvidingDifferentTextureSpecId)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::TextureManager sut(stubGraphicsDevice);
        Cocoa::Graphics::TextureSpec spec1{ .Id = "default" };
        Cocoa::Graphics::TextureSpec spec2{ .Id = "non-default" };

        Cocoa::Graphics::TextureHandle result1 = sut.Load(spec1, "pixels");
        Cocoa::Graphics::TextureHandle result2 = sut.Load(spec2, "pixels");

        EXPECT_NE(result1.Id, result2.Id);
    }

    TEST(TextureManagerTests, Get_ShouldReturnTexture2D_WhenProvidingValidHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::TextureManager sut(stubGraphicsDevice);
        Cocoa::Graphics::TextureSpec spec{ .Id = "default" };

        Cocoa::Graphics::TextureHandle handle = sut.Load(spec, "default");
        const Cocoa::Graphics::Texture2D& texture = sut.Get(handle);

        EXPECT_NE(&texture, nullptr);
    }

    TEST(TextureManagerTests, Get_ShouldReturnDifferentTexture_WhenProvidingDifferentHandles)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::TextureManager sut(stubGraphicsDevice);
        Cocoa::Graphics::TextureSpec spec1{ .Id = "default" };
        Cocoa::Graphics::TextureSpec spec2{ .Id = "non-default" };

        Cocoa::Graphics::TextureHandle handle1 = sut.Load(spec1, "pixels");
        Cocoa::Graphics::TextureHandle handle2 = sut.Load(spec2, "pixels");
        const Cocoa::Graphics::Texture2D& texture1 = sut.Get(handle1);
        const Cocoa::Graphics::Texture2D& texture2 = sut.Get(handle2);

        EXPECT_NE(&texture1, &texture2);
    }

    TEST(TextureManagerTests, Get_ShouldReturnSameTexture_WhenProvidingSameHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::TextureManager sut(stubGraphicsDevice);
        Cocoa::Graphics::TextureSpec spec{ .Id = "default" };

        Cocoa::Graphics::TextureHandle handle = sut.Load(spec, "pixels");
        const Cocoa::Graphics::Texture2D& texture1 = sut.Get(handle);
        const Cocoa::Graphics::Texture2D& texture2 = sut.Get(handle);

        EXPECT_EQ(&texture1, &texture2);
    }

    TEST(TextureManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::TextureManager sut(stubGraphicsDevice);

        Cocoa::Graphics::TextureHandle handle{ .Id = 9999 };

        EXPECT_THROW(
            {
                sut.Get(handle);
            },
            std::runtime_error
        );
    }

    TEST(TextureManagerTests, TryGetHandle_ShouldReturnTrueAndOutHandle_WhenIdExists)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::TextureManager sut(stubGraphicsDevice);
        Cocoa::Graphics::TextureSpec spec{ .Id = "default" };
        Cocoa::Graphics::TextureHandle expectedHandle = sut.Load(spec, "pixels");

        Cocoa::Graphics::TextureHandle outHandle;
        bool result = sut.TryGetHandle(spec.Id, outHandle);

        EXPECT_TRUE(result);
        EXPECT_EQ(outHandle.Id, expectedHandle.Id);
    }

    TEST(TextureManagerTests, TryGetHandle_ShouldReturnFalseAndOutHandle_WhenIdDoesNotExist)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::TextureManager sut(stubGraphicsDevice);
        Cocoa::Graphics::TextureSpec spec{ .Id = "default" };
        sut.Load(spec, "pixels");

        Cocoa::Graphics::TextureHandle outHandle;
        bool result = sut.TryGetHandle("badId", outHandle);

        EXPECT_FALSE(result);
        EXPECT_EQ(outHandle.Id, 0);
    }
}