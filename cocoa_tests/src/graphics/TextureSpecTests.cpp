#include "graphics/TextureSpec.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

namespace CocoaTests::Graphics
{
    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGB8_WhenValueIsRGB8)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFormat("rgb8", 3);

        EXPECT_EQ(result, cocoa::Graphics::TextureFormat::RGB8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGBA8_WhenValueIsRGBA8)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFormat("rgba8", 4);

        EXPECT_EQ(result, cocoa::Graphics::TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGB8_WhenValueIsAutoAndImageHasThreeChannels)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFormat("auto", 3);

        EXPECT_EQ(result, cocoa::Graphics::TextureFormat::RGB8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGBA8_WhenValueIsAutoAndImageHasFourChannels)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFormat("auto", 4);

        EXPECT_EQ(result, cocoa::Graphics::TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldNormalizeValue_WhenValueHasUppercase)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFormat("RGBA8", 4);

        EXPECT_EQ(result, cocoa::Graphics::TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(cocoa::Graphics::TextureSpec::ParseFormat("bad-format", 4), std::runtime_error);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearest_WhenValueIsNearest)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFilter("nearest");

        EXPECT_EQ(result, cocoa::Graphics::TextureFilter::Nearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinear_WhenValueIsLinear)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFilter("linear");

        EXPECT_EQ(result, cocoa::Graphics::TextureFilter::Linear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearestMipmapNearest_WhenValueIsNearestMipmapNearest)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFilter("nearest_mipmap_nearest");

        EXPECT_EQ(result, cocoa::Graphics::TextureFilter::NearestMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinearMipmapNearest_WhenValueIsLinearMipmapNearest)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFilter("linear_mipmap_nearest");

        EXPECT_EQ(result, cocoa::Graphics::TextureFilter::LinearMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearestMipmapLinear_WhenValueIsNearestMipmapLinear)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFilter("nearest_mipmap_linear");

        EXPECT_EQ(result, cocoa::Graphics::TextureFilter::NearestMipmapLinear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinearMipmapLinear_WhenValueIsLinearMipmapLinear)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseFilter("linear_mipmap_linear");

        EXPECT_EQ(result, cocoa::Graphics::TextureFilter::LinearMipmapLinear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldNormalizeValue_WhenValueHasUppercaseUnderscoresSpacesOrHyphens)
    {
        EXPECT_EQ(cocoa::Graphics::TextureSpec::ParseFilter("NEAREST_MIPMAP_NEAREST"), cocoa::Graphics::TextureFilter::NearestMipmapNearest);
        EXPECT_EQ(cocoa::Graphics::TextureSpec::ParseFilter("nearest mipmap linear"), cocoa::Graphics::TextureFilter::NearestMipmapLinear);
        EXPECT_EQ(cocoa::Graphics::TextureSpec::ParseFilter("linear-mipmap-linear"), cocoa::Graphics::TextureFilter::LinearMipmapLinear);
        EXPECT_EQ(cocoa::Graphics::TextureSpec::ParseFilter("LinearMipmapNearest"), cocoa::Graphics::TextureFilter::LinearMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(cocoa::Graphics::TextureSpec::ParseFilter("bad-filter"), std::runtime_error);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldReturnRepeat_WhenValueIsRepeat)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseWrap("repeat");

        EXPECT_EQ(result, cocoa::Graphics::TextureWrap::Repeat);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldReturnClampToEdge_WhenValueIsClampToEdge)
    {
        const auto result = cocoa::Graphics::TextureSpec::ParseWrap("clamp_to_edge");

        EXPECT_EQ(result, cocoa::Graphics::TextureWrap::ClampToEdge);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldNormalizeValue_WhenValueHasUppercaseUnderscoresSpacesOrHyphens)
    {
        EXPECT_EQ(cocoa::Graphics::TextureSpec::ParseWrap("CLAMP_TO_EDGE"), cocoa::Graphics::TextureWrap::ClampToEdge);
        EXPECT_EQ(cocoa::Graphics::TextureSpec::ParseWrap("clamp to edge"), cocoa::Graphics::TextureWrap::ClampToEdge);
        EXPECT_EQ(cocoa::Graphics::TextureSpec::ParseWrap("clamp-to-edge"), cocoa::Graphics::TextureWrap::ClampToEdge);
        EXPECT_EQ(cocoa::Graphics::TextureSpec::ParseWrap("ClampToEdge"), cocoa::Graphics::TextureWrap::ClampToEdge);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(cocoa::Graphics::TextureSpec::ParseWrap("bad-wrap"), std::runtime_error);
    }
}