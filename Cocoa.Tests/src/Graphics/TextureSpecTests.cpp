#include "Graphics/TextureSpec.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

namespace Cocoa::Graphics::Tests
{
    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGB8_WhenValueIsRGB8)
    {
        const auto result = Graphics::TextureSpec::ParseFormat("rgb8", 3);

        EXPECT_EQ(result, TextureFormat::RGB8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGBA8_WhenValueIsRGBA8)
    {
        const auto result = Graphics::TextureSpec::ParseFormat("rgba8", 4);

        EXPECT_EQ(result, TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGB8_WhenValueIsAutoAndImageHasThreeChannels)
    {
        const auto result = Graphics::TextureSpec::ParseFormat("auto", 3);

        EXPECT_EQ(result, TextureFormat::RGB8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGBA8_WhenValueIsAutoAndImageHasFourChannels)
    {
        const auto result = Graphics::TextureSpec::ParseFormat("auto", 4);

        EXPECT_EQ(result, TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldNormalizeValue_WhenValueHasUppercase)
    {
        const auto result = Graphics::TextureSpec::ParseFormat("RGBA8", 4);

        EXPECT_EQ(result, TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(TextureSpec::ParseFormat("bad-format", 4), std::runtime_error);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearest_WhenValueIsNearest)
    {
        const auto result = Graphics::TextureSpec::ParseFilter("nearest");

        EXPECT_EQ(result, TextureFilter::Nearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinear_WhenValueIsLinear)
    {
        const auto result = Graphics::TextureSpec::ParseFilter("linear");

        EXPECT_EQ(result, TextureFilter::Linear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearestMipmapNearest_WhenValueIsNearestMipmapNearest)
    {
        const auto result = Graphics::TextureSpec::ParseFilter("nearest_mipmap_nearest");

        EXPECT_EQ(result, TextureFilter::NearestMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinearMipmapNearest_WhenValueIsLinearMipmapNearest)
    {
        const auto result = Graphics::TextureSpec::ParseFilter("linear_mipmap_nearest");

        EXPECT_EQ(result, TextureFilter::LinearMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearestMipmapLinear_WhenValueIsNearestMipmapLinear)
    {
        const auto result = Graphics::TextureSpec::ParseFilter("nearest_mipmap_linear");

        EXPECT_EQ(result, TextureFilter::NearestMipmapLinear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinearMipmapLinear_WhenValueIsLinearMipmapLinear)
    {
        const auto result = Graphics::TextureSpec::ParseFilter("linear_mipmap_linear");

        EXPECT_EQ(result, TextureFilter::LinearMipmapLinear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldNormalizeValue_WhenValueHasUppercaseUnderscoresSpacesOrHyphens)
    {
        EXPECT_EQ(TextureSpec::ParseFilter("NEAREST_MIPMAP_NEAREST"), TextureFilter::NearestMipmapNearest);
        EXPECT_EQ(TextureSpec::ParseFilter("nearest mipmap linear"), TextureFilter::NearestMipmapLinear);
        EXPECT_EQ(TextureSpec::ParseFilter("linear-mipmap-linear"), TextureFilter::LinearMipmapLinear);
        EXPECT_EQ(TextureSpec::ParseFilter("LinearMipmapNearest"), TextureFilter::LinearMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(TextureSpec::ParseFilter("bad-filter"), std::runtime_error);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldReturnRepeat_WhenValueIsRepeat)
    {
        const auto result = Graphics::TextureSpec::ParseWrap("repeat");

        EXPECT_EQ(result, TextureWrap::Repeat);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldReturnClampToEdge_WhenValueIsClampToEdge)
    {
        const auto result = Graphics::TextureSpec::ParseWrap("clamp_to_edge");

        EXPECT_EQ(result, TextureWrap::ClampToEdge);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldNormalizeValue_WhenValueHasUppercaseUnderscoresSpacesOrHyphens)
    {
        EXPECT_EQ(TextureSpec::ParseWrap("CLAMP_TO_EDGE"), TextureWrap::ClampToEdge);
        EXPECT_EQ(TextureSpec::ParseWrap("clamp to edge"), TextureWrap::ClampToEdge);
        EXPECT_EQ(TextureSpec::ParseWrap("clamp-to-edge"), TextureWrap::ClampToEdge);
        EXPECT_EQ(TextureSpec::ParseWrap("ClampToEdge"), TextureWrap::ClampToEdge);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(TextureSpec::ParseWrap("bad-wrap"), std::runtime_error);
    }
}