#include <Graphics/Renderer2D.hpp>
#include <Graphics/SpriteManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/TextureManager.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/RenderStatistics.hpp>
#include <Graphics/TextureSpec.hpp>
#include "Stubs/Graphics/StubGraphicsDevice.hpp"

#include <gtest/gtest.h>

namespace CocoaTests::Graphics
{
    TEST(Renderer2DTests, EndDraw_ShouldSortDrawSubmissionOrder_WhenGivenDrawSubmissions)
    {
        const std::vector<Cocoa::Graphics::DrawSubmissionInfo> submissions
        {
            {0, 3, Cocoa::Graphics::SortLayer::Background, Cocoa::Graphics::DrawSubmissionType::RawQuad},
            {1, 0, Cocoa::Graphics::SortLayer::Background, Cocoa::Graphics::DrawSubmissionType::RawQuad},
            {2, 1, Cocoa::Graphics::SortLayer::Background, Cocoa::Graphics::DrawSubmissionType::RawQuad},
            {3, 2, Cocoa::Graphics::SortLayer::Background, Cocoa::Graphics::DrawSubmissionType::RawQuad}
        };

        constexpr std::array<size_t, 4> expectedSubmissionOrder{1, 2, 3, 0};

        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;

        Cocoa::Graphics::Renderer2D sut(
            stubGraphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager
        );

        auto shaderHandle = shaderManager.Load("test_shader", "", "");

        const Cocoa::Graphics::TextureSpec spec{
            .Id = "test_texture",
            .Width = 2,
            .Height = 2
        };

        constexpr std::array<unsigned char, 16> pixels{
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255
        };

        auto textureHandle = textureManager.Load(spec, pixels.data());

        auto materialHandle = materialManager.Load(
            "test_material",
            shaderHandle,
            "alpha",
            Cocoa::Core::Color{}
        );

        constexpr Cocoa::Math::Matrix4f modelMatrix{};
        constexpr Cocoa::Math::Vector2f tilingFactor{};

        sut.BeginDraw(Cocoa::Math::Matrix4f{});

        for (const auto& submission : submissions)
        {
            sut.DrawQuad(
                modelMatrix,
                materialHandle,
                textureHandle,
                tilingFactor,
                submission.SortingLayer,
                submission.SortingOrder
            );
        }

        sut.EndDraw();

        const auto& actual = sut.GetRenderStatistics().DrawSubmissionsInfo;

        ASSERT_EQ(expectedSubmissionOrder.size(), actual.size());

        for (size_t i = 0; i < expectedSubmissionOrder.size(); ++i)
        {
            const auto& expected = submissions[expectedSubmissionOrder[i]];

            EXPECT_EQ(expectedSubmissionOrder[i], actual[i].Index);
            EXPECT_EQ(expected.SortingOrder, actual[i].SortingOrder);
            EXPECT_EQ(expected.SortingLayer, actual[i].SortingLayer);
            EXPECT_EQ(expected.SubmissionType, actual[i].SubmissionType);
        }
    }

    TEST(Renderer2DTests, EndDraw_ShouldSortMixedDrawSubmissions_WhenGivenSpritesAndRawQuads)
    {
        const std::vector<Cocoa::Graphics::DrawSubmissionInfo> submissions
        {
            {0, 2, Cocoa::Graphics::SortLayer::World, Cocoa::Graphics::DrawSubmissionType::RawQuad},
            {1, 0, Cocoa::Graphics::SortLayer::UI, Cocoa::Graphics::DrawSubmissionType::Sprite},
            {2, 1, Cocoa::Graphics::SortLayer::Background, Cocoa::Graphics::DrawSubmissionType::Sprite},
            {3, 1, Cocoa::Graphics::SortLayer::Background, Cocoa::Graphics::DrawSubmissionType::RawQuad},
            {4, 2, Cocoa::Graphics::SortLayer::World, Cocoa::Graphics::DrawSubmissionType::Sprite}
        };

        constexpr std::array<size_t, 5> expectedSubmissionOrder{2, 3, 0, 4, 1};

        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::ShaderManager shaderManager(stubGraphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(stubGraphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;

        Cocoa::Graphics::Renderer2D sut(
            stubGraphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager
        );

        const auto shaderHandle = shaderManager.Load("test_shader", "", "");

        const Cocoa::Graphics::TextureSpec spec{
            .Id = "test_texture",
            .Width = 2,
            .Height = 2
        };

        constexpr std::array<unsigned char, 16> pixels{
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255
        };

        const auto textureHandle = textureManager.Load(spec, pixels.data());

        const auto materialHandle = materialManager.Load(
            "test_material",
            shaderHandle,
            "alpha",
            Cocoa::Core::Color{}
        );

        const auto spriteHandle = spriteManager.Load(
            "test_sprite",
            textureHandle,
            Cocoa::Math::Vector2f{0.0f, 0.0f},
            Cocoa::Math::Vector2f{2.0f, 2.0f},
            Cocoa::Math::Vector2f{2.0f, 2.0f}
        );

        constexpr Cocoa::Math::Matrix4f modelMatrix{};
        constexpr Cocoa::Math::Vector2f tilingFactor{};

        sut.BeginDraw(Cocoa::Math::Matrix4f{});

        for (const auto& submission : submissions)
        {
            if (submission.SubmissionType == Cocoa::Graphics::DrawSubmissionType::RawQuad)
            {
                sut.DrawQuad(
                    modelMatrix,
                    materialHandle,
                    textureHandle,
                    tilingFactor,
                    submission.SortingLayer,
                    submission.SortingOrder
                );
            }
            else
            {
                sut.DrawQuad(
                    modelMatrix,
                    materialHandle,
                    spriteHandle,
                    tilingFactor,
                    false,
                    false,
                    submission.SortingLayer,
                    submission.SortingOrder
                );
            }
        }

        sut.EndDraw();

        const auto& actual = sut.GetRenderStatistics().DrawSubmissionsInfo;

        ASSERT_EQ(expectedSubmissionOrder.size(), actual.size());

        for (size_t i = 0; i < expectedSubmissionOrder.size(); ++i)
        {
            const auto& expected = submissions[expectedSubmissionOrder[i]];

            EXPECT_EQ(expectedSubmissionOrder[i], actual[i].Index);
            EXPECT_EQ(expected.SortingOrder, actual[i].SortingOrder);
            EXPECT_EQ(expected.SortingLayer, actual[i].SortingLayer);
            EXPECT_EQ(expected.SubmissionType, actual[i].SubmissionType);
        }
    }
}