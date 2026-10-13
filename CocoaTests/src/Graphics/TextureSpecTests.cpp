#include "Graphics/TextureSpec.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

namespace CocoaTests::Graphics
{
    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGB8_WhenValueIsRGB8)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFormat("rgb8", 3);

        EXPECT_EQ(result, Cocoa::Graphics::TextureFormat::RGB8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGBA8_WhenValueIsRGBA8)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFormat("rgba8", 4);

        EXPECT_EQ(result, Cocoa::Graphics::TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGB8_WhenValueIsAutoAndImageHasThreeChannels)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFormat("auto", 3);

        EXPECT_EQ(result, Cocoa::Graphics::TextureFormat::RGB8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGBA8_WhenValueIsAutoAndImageHasFourChannels)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFormat("auto", 4);

        EXPECT_EQ(result, Cocoa::Graphics::TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldNormalizeValue_WhenValueHasUppercase)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFormat("RGBA8", 4);

        EXPECT_EQ(result, Cocoa::Graphics::TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(Cocoa::Graphics::TextureSpec::ParseFormat("bad-format", 4), std::runtime_error);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearest_WhenValueIsNearest)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFilter("nearest");

        EXPECT_EQ(result, Cocoa::Graphics::TextureFilter::Nearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinear_WhenValueIsLinear)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFilter("linear");

        EXPECT_EQ(result, Cocoa::Graphics::TextureFilter::Linear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearestMipmapNearest_WhenValueIsNearestMipmapNearest)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFilter("nearest_mipmap_nearest");

        EXPECT_EQ(result, Cocoa::Graphics::TextureFilter::NearestMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinearMipmapNearest_WhenValueIsLinearMipmapNearest)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFilter("linear_mipmap_nearest");

        EXPECT_EQ(result, Cocoa::Graphics::TextureFilter::LinearMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearestMipmapLinear_WhenValueIsNearestMipmapLinear)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFilter("nearest_mipmap_linear");

        EXPECT_EQ(result, Cocoa::Graphics::TextureFilter::NearestMipmapLinear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinearMipmapLinear_WhenValueIsLinearMipmapLinear)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseFilter("linear_mipmap_linear");

        EXPECT_EQ(result, Cocoa::Graphics::TextureFilter::LinearMipmapLinear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldNormalizeValue_WhenValueHasUppercaseUnderscoresSpacesOrHyphens)
    {
        EXPECT_EQ(Cocoa::Graphics::TextureSpec::ParseFilter("NEAREST_MIPMAP_NEAREST"), Cocoa::Graphics::TextureFilter::NearestMipmapNearest);
        EXPECT_EQ(Cocoa::Graphics::TextureSpec::ParseFilter("nearest mipmap linear"), Cocoa::Graphics::TextureFilter::NearestMipmapLinear);
        EXPECT_EQ(Cocoa::Graphics::TextureSpec::ParseFilter("linear-mipmap-linear"), Cocoa::Graphics::TextureFilter::LinearMipmapLinear);
        EXPECT_EQ(Cocoa::Graphics::TextureSpec::ParseFilter("LinearMipmapNearest"), Cocoa::Graphics::TextureFilter::LinearMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(Cocoa::Graphics::TextureSpec::ParseFilter("bad-filter"), std::runtime_error);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldReturnRepeat_WhenValueIsRepeat)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseWrap("repeat");

        EXPECT_EQ(result, Cocoa::Graphics::TextureWrap::Repeat);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldReturnClampToEdge_WhenValueIsClampToEdge)
    {
        const auto result = Cocoa::Graphics::TextureSpec::ParseWrap("clamp_to_edge");

        EXPECT_EQ(result, Cocoa::Graphics::TextureWrap::ClampToEdge);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldNormalizeValue_WhenValueHasUppercaseUnderscoresSpacesOrHyphens)
    {
        EXPECT_EQ(Cocoa::Graphics::TextureSpec::ParseWrap("CLAMP_TO_EDGE"), Cocoa::Graphics::TextureWrap::ClampToEdge);
        EXPECT_EQ(Cocoa::Graphics::TextureSpec::ParseWrap("clamp to edge"), Cocoa::Graphics::TextureWrap::ClampToEdge);
        EXPECT_EQ(Cocoa::Graphics::TextureSpec::ParseWrap("clamp-to-edge"), Cocoa::Graphics::TextureWrap::ClampToEdge);
        EXPECT_EQ(Cocoa::Graphics::TextureSpec::ParseWrap("ClampToEdge"), Cocoa::Graphics::TextureWrap::ClampToEdge);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(Cocoa::Graphics::TextureSpec::ParseWrap("bad-wrap"), std::runtime_error);
    }
}