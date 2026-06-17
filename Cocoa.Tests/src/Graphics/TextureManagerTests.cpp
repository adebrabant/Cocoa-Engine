#include "Stubs/Graphics/StubGraphicsDevice.hpp"
#include "Stubs/Graphics/StubTexture2D.hpp"
#include <Graphics/TextureManager.hpp>
#include <Graphics/TextureSpec.hpp>
#include <gtest/gtest.h>
#include <stdexcept>

namespace Cocoa::Graphics::Tests
{
    TEST(TextureManagerTests, Load_ShouldReturnTextureHandle_WhenProvidingValidValues)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::TextureManager sut(stubGraphicsDevice);
        Graphics::TextureSpec spec;

        TextureHandle result = sut.Load(spec, "pixels");

        EXPECT_EQ(result.Id, 1);
    }

    TEST(TextureManagerTests, Load_ShouldReturnSameTextureHandleId_WhenProvidingSameTextureSpecId)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::TextureManager sut(stubGraphicsDevice);
        Graphics::TextureSpec spec { .Id = "default" };

        TextureHandle result1 = sut.Load(spec, "pixels");
        TextureHandle result2 = sut.Load(spec, "pixels");

        EXPECT_EQ(result1.Id, result2.Id);
    }

    TEST(TextureManagerTests, Load_ShouldReturnDifferentTextureHandleId_WhenProvidingDifferentTextureSpecId)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::TextureManager sut(stubGraphicsDevice);
        Graphics::TextureSpec spec1{ .Id = "default" };
        Graphics::TextureSpec spec2{ .Id = "non-default" };

        TextureHandle result1 = sut.Load(spec1, "pixels");
        TextureHandle result2 = sut.Load(spec2, "pixels");

        EXPECT_NE(result1.Id, result2.Id);
    }

    TEST(TextureManagerTests, Get_ShouldReturnTexture2D_WhenProvidingValidHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::TextureManager sut(stubGraphicsDevice);
        Graphics::TextureSpec spec{ .Id = "default" };

        TextureHandle handle = sut.Load(spec, "default");
        const Graphics::Texture2D& texture = sut.Get(handle);

        EXPECT_NE(&texture, nullptr);
    }

    TEST(TextureManagerTests, Get_ShouldReturnDifferentTexture_WhenProvidingDifferentHandles)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::TextureManager sut(stubGraphicsDevice);
        Graphics::TextureSpec spec1{ .Id = "default" };
        Graphics::TextureSpec spec2{ .Id = "non-default" };

        TextureHandle handle1 = sut.Load(spec1, "pixels");
        TextureHandle handle2 = sut.Load(spec2, "pixels");
        const Graphics::Texture2D& texture1 = sut.Get(handle1);
        const Graphics::Texture2D& texture2 = sut.Get(handle2);

        EXPECT_NE(&texture1, &texture2);
    }

    TEST(TextureManagerTests, Get_ShouldReturnSameTexture_WhenProvidingSameHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::TextureManager sut(stubGraphicsDevice);
        Graphics::TextureSpec spec{ .Id = "default" };

        TextureHandle handle = sut.Load(spec, "pixels");
        const Graphics::Texture2D& texture1 = sut.Get(handle);
        const Graphics::Texture2D& texture2 = sut.Get(handle);

        EXPECT_EQ(&texture1, &texture2);
    }

    TEST(TextureManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::TextureManager sut(stubGraphicsDevice);

        TextureHandle handle{ .Id = 9999 };

        EXPECT_THROW(
            {
                sut.Get(handle);
            },
            std::runtime_error
        );
    }
}