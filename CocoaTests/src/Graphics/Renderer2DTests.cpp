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
        struct Submission
        {
            float X;
            int SortingOrder;
        };

        constexpr std::array submissions{
            Submission{30.0f, 3},
            Submission{10.0f, 0},
            Submission{20.0f, 1},
            Submission{40.0f, 2}
        };

        // Expected first-vertex X coordinates after sorting.
        constexpr std::array expectedX{
            9.5f, 19.5f, 39.5f, 29.5f
        };

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

        constexpr Cocoa::Math::Vector2f tilingFactor{};

        sut.BeginDraw(Cocoa::Math::Matrix4f{});

        for (const auto& submission : submissions)
        {
            const auto modelMatrix = Cocoa::Math::Matrix4f::Translation(
                Cocoa::Math::Vector2f{submission.X, 0.0f}
            );

            sut.DrawQuad(
                modelMatrix,
                materialHandle,
                textureHandle,
                tilingFactor,
                Cocoa::Graphics::SortLayer::Background,
                submission.SortingOrder
            );
        }

        sut.EndDraw();

        const auto& capture = stubGraphicsDevice.GetVertexBufferCapture();

        ASSERT_GT(capture.Stride, 0u);
        ASSERT_EQ(expectedX.size() * 4 * capture.Stride, capture.Data.size());

        for (size_t i = 0; i < expectedX.size(); ++i)
        {
            float actualX{};

            const size_t offset = i * 4 * capture.Stride;

            std::memcpy(
                &actualX,
                capture.Data.data() + offset,
                sizeof(float)
            );

            EXPECT_FLOAT_EQ(expectedX[i], actualX);
        }
    }

    TEST(Renderer2DTests, EndDraw_ShouldSortMixedDrawSubmissions_WhenGivenSpritesAndRawQuads)
    {
        enum class TestDrawType
        {
            RawQuad,
            Sprite
        };

        struct TestSubmission
        {
            float X;
            int SortingOrder;
            Cocoa::Graphics::SortLayer SortingLayer;
            TestDrawType DrawType;
        };

        constexpr std::array testSubmissions{
            TestSubmission{10.0f, 2, Cocoa::Graphics::SortLayer::World, TestDrawType::RawQuad},
            TestSubmission{20.0f, 0, Cocoa::Graphics::SortLayer::UI, TestDrawType::Sprite},
            TestSubmission{30.0f, 1, Cocoa::Graphics::SortLayer::Background, TestDrawType::Sprite},
            TestSubmission{40.0f, 1, Cocoa::Graphics::SortLayer::Background, TestDrawType::RawQuad},
            TestSubmission{50.0f, 2, Cocoa::Graphics::SortLayer::World, TestDrawType::Sprite}
        };

        // Expected submission indices: 2, 3, 0, 4, 1.
        // Equal sorting keys must retain insertion order.
        constexpr std::array expectedX{
            29.5f, 39.5f, 9.5f, 49.5f, 19.5f
        };

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

        constexpr Cocoa::Math::Vector2f tilingFactor{};

        sut.BeginDraw(Cocoa::Math::Matrix4f{});

        for (const auto& testSubmission : testSubmissions)
        {
            const auto modelMatrix = Cocoa::Math::Matrix4f::Translation(
                Cocoa::Math::Vector2f{testSubmission.X, 0.0f}
            );

            switch (testSubmission.DrawType)
            {
            case TestDrawType::RawQuad:
                sut.DrawQuad(
                    modelMatrix,
                    materialHandle,
                    textureHandle,
                    tilingFactor,
                    testSubmission.SortingLayer,
                    testSubmission.SortingOrder
                );
                break;
            case TestDrawType::Sprite:
                sut.DrawQuad(
                    modelMatrix,
                    materialHandle,
                    spriteHandle,
                    tilingFactor,
                    false,
                    false,
                    testSubmission.SortingLayer,
                    testSubmission.SortingOrder
                );
                break;
            }
        }

        sut.EndDraw();

        const auto& capture = stubGraphicsDevice.GetVertexBufferCapture();

        ASSERT_GT(capture.Stride, 0u);
        ASSERT_EQ(expectedX.size() * 4 * capture.Stride, capture.Data.size());

        for (size_t i = 0; i < expectedX.size(); ++i)
        {
            float actualX{};

            const size_t offset = i * 4 * capture.Stride;

            std::memcpy(
                &actualX,
                capture.Data.data() + offset,
                sizeof(float)
            );

            EXPECT_FLOAT_EQ(expectedX[i], actualX);
        }
    }
}