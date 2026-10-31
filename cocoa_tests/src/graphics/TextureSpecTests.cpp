#include "graphics/TextureSpec.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

namespace cocoa_tests::graphics
{
    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGB8_WhenValueIsRGB8)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFormat("rgb8", 3);

        EXPECT_EQ(result, cocoa::graphics::TextureFormat::RGB8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGBA8_WhenValueIsRGBA8)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFormat("rgba8", 4);

        EXPECT_EQ(result, cocoa::graphics::TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGB8_WhenValueIsAutoAndImageHasThreeChannels)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFormat("auto", 3);

        EXPECT_EQ(result, cocoa::graphics::TextureFormat::RGB8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldReturnRGBA8_WhenValueIsAutoAndImageHasFourChannels)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFormat("auto", 4);

        EXPECT_EQ(result, cocoa::graphics::TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldNormalizeValue_WhenValueHasUppercase)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFormat("RGBA8", 4);

        EXPECT_EQ(result, cocoa::graphics::TextureFormat::RGBA8);
    }

    TEST(TextureSpecTests, ParseFormat_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(cocoa::graphics::TextureSpec::parseFormat("bad-format", 4), std::runtime_error);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearest_WhenValueIsNearest)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFilter("nearest");

        EXPECT_EQ(result, cocoa::graphics::TextureFilter::Nearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinear_WhenValueIsLinear)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFilter("linear");

        EXPECT_EQ(result, cocoa::graphics::TextureFilter::Linear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearestMipmapNearest_WhenValueIsNearestMipmapNearest)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFilter("nearest_mipmap_nearest");

        EXPECT_EQ(result, cocoa::graphics::TextureFilter::NearestMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinearMipmapNearest_WhenValueIsLinearMipmapNearest)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFilter("linear_mipmap_nearest");

        EXPECT_EQ(result, cocoa::graphics::TextureFilter::LinearMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnNearestMipmapLinear_WhenValueIsNearestMipmapLinear)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFilter("nearest_mipmap_linear");

        EXPECT_EQ(result, cocoa::graphics::TextureFilter::NearestMipmapLinear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldReturnLinearMipmapLinear_WhenValueIsLinearMipmapLinear)
    {
        const auto result = cocoa::graphics::TextureSpec::parseFilter("linear_mipmap_linear");

        EXPECT_EQ(result, cocoa::graphics::TextureFilter::LinearMipmapLinear);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldNormalizeValue_WhenValueHasUppercaseUnderscoresSpacesOrHyphens)
    {
        EXPECT_EQ(cocoa::graphics::TextureSpec::parseFilter("NEAREST_MIPMAP_NEAREST"), cocoa::graphics::TextureFilter::NearestMipmapNearest);
        EXPECT_EQ(cocoa::graphics::TextureSpec::parseFilter("nearest mipmap linear"), cocoa::graphics::TextureFilter::NearestMipmapLinear);
        EXPECT_EQ(cocoa::graphics::TextureSpec::parseFilter("linear-mipmap-linear"), cocoa::graphics::TextureFilter::LinearMipmapLinear);
        EXPECT_EQ(cocoa::graphics::TextureSpec::parseFilter("LinearMipmapNearest"), cocoa::graphics::TextureFilter::LinearMipmapNearest);
    }

    TEST(TextureSpecTests, ParseFilter_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(cocoa::graphics::TextureSpec::parseFilter("bad-filter"), std::runtime_error);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldReturnRepeat_WhenValueIsRepeat)
    {
        const auto result = cocoa::graphics::TextureSpec::parseWrap("repeat");

        EXPECT_EQ(result, cocoa::graphics::TextureWrap::Repeat);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldReturnClampToEdge_WhenValueIsClampToEdge)
    {
        const auto result = cocoa::graphics::TextureSpec::parseWrap("clamp_to_edge");

        EXPECT_EQ(result, cocoa::graphics::TextureWrap::ClampToEdge);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldNormalizeValue_WhenValueHasUppercaseUnderscoresSpacesOrHyphens)
    {
        EXPECT_EQ(cocoa::graphics::TextureSpec::parseWrap("CLAMP_TO_EDGE"), cocoa::graphics::TextureWrap::ClampToEdge);
        EXPECT_EQ(cocoa::graphics::TextureSpec::parseWrap("clamp to edge"), cocoa::graphics::TextureWrap::ClampToEdge);
        EXPECT_EQ(cocoa::graphics::TextureSpec::parseWrap("clamp-to-edge"), cocoa::graphics::TextureWrap::ClampToEdge);
        EXPECT_EQ(cocoa::graphics::TextureSpec::parseWrap("ClampToEdge"), cocoa::graphics::TextureWrap::ClampToEdge);
    }

    TEST(TextureSpecTests, ParseWrap_ShouldThrow_WhenValueIsInvalid)
    {
        EXPECT_THROW(cocoa::graphics::TextureSpec::parseWrap("bad-wrap"), std::runtime_error);
    }
}
