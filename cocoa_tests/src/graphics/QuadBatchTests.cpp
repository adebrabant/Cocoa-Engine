#include <graphics/MaterialManager.hpp>
#include <graphics/QuadBatch.hpp>
#include <graphics/RenderStatistics.hpp>
#include <graphics/ShaderManager.hpp>
#include <graphics/SpriteManager.hpp>
#include <graphics/TextureManager.hpp>
#include <graphics/TextureSpec.hpp>
#include <gtest/gtest.h>
#include <stubs/Graphics/StubGraphicsDevice.hpp>

#include <vector>

namespace CocoaTests::Graphics
{
    static std::vector<cocoa::Graphics::SpriteHandle> CreateSpritesWithUniqueTextures(
        cocoa::Graphics::TextureManager& textureManager,
        cocoa::Graphics::SpriteManager& spriteManager,
        const int count)
    {
        std::vector<cocoa::Graphics::SpriteHandle> handles;
        constexpr uint8_t pixelData[] {255, 255, 255, 255};

        for (auto i = 0; i < count; ++i)
        {
            const cocoa::Graphics::TextureSpec textureSpec
            {
                .Id = "test-texture-" + std::to_string(i),
                .Width = 256,
                .Height = 256
            };

            const cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
                textureSpec,
                pixelData
            );

            const cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
                "sprite-" + std::to_string(i),
                textureHandle,
                cocoa::Math::Vector2f(0.0f, 0.0f),
                cocoa::Math::Vector2f(256.0f, 256.0f),
                cocoa::Math::Vector2f(256.0f, 256.0f)
            );

            handles.emplace_back(spriteHandle);
        }

        return handles;
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGivenDuplicateShaders)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        constexpr cocoa::Core::Color tint;

        const cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::Math::Vector2f(0.0f, 0.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        sut.Draw(
            identity,
            materialHandleA,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.Draw(
            identity,
            materialHandleB,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.Flush(identity);

        EXPECT_EQ(1, renderStats.DrawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenShaderChanges)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandleOne = shaderManager.Load(
            "test-shader-1",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::ShaderHandle shaderHandleTwo = shaderManager.Load(
            "test-shader-2",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        constexpr cocoa::Core::Color tint;

        const cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandleOne,
            "opaque",
            tint
        );

        const cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandleTwo,
            "opaque",
            tint
        );

        const cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::Math::Vector2f(0.0f, 0.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        sut.Draw(
            identity,
            materialHandleA,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.Draw(
            identity,
            materialHandleB,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.Flush(identity);

        EXPECT_EQ(2, renderStats.DrawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenTextureChanges)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::TextureSpec textureSpecOne
        {
            .Id = "test-texture-01",
            .Width = 256,
            .Height = 256
        };

        const cocoa::Graphics::TextureSpec textureSpecTwo
        {
            .Id = "test-texture-02",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::Graphics::TextureHandle textureHandleOne = textureManager.Load(
            textureSpecOne,
            pixelData
        );

        const cocoa::Graphics::TextureHandle textureHandleTwo = textureManager.Load(
            textureSpecTwo,
            pixelData
        );

        constexpr cocoa::Core::Color tint;

        const cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::Graphics::SpriteHandle spriteHandleA = spriteManager.Load(
            "default-sprite-a",
            textureHandleOne,
            cocoa::Math::Vector2f(0.0f, 0.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        const cocoa::Graphics::SpriteHandle spriteHandleB = spriteManager.Load(
            "default-sprite-b",
            textureHandleTwo,
            cocoa::Math::Vector2f(0.0f, 0.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        sut.Draw(
            identity,
            materialHandleA,
            spriteHandleA,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.Draw(
            identity,
            materialHandleB,
            spriteHandleB,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.Flush(identity);

        EXPECT_EQ(1, renderStats.DrawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenOnlyTintChanges)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "opaque",
            cocoa::Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite-b",
            textureHandle,
            cocoa::Math::Vector2f(0.0f, 0.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        sut.Draw(
            identity,
            materialHandleA,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.Draw(
            identity,
            materialHandleB,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.Flush(identity);

        EXPECT_EQ(1, renderStats.DrawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenGivenDifferentBlendMode)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "alpha",
            cocoa::Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite-b",
            textureHandle,
            cocoa::Math::Vector2f(0.0f, 0.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        sut.Draw(
            identity,
            materialHandleA,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.Draw(
            identity,
            materialHandleB,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.Flush(identity);

        EXPECT_EQ(2, renderStats.DrawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenGiven33UniqueTextures)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const std::vector<cocoa::Graphics::SpriteHandle> spriteHandles =
            CreateSpritesWithUniqueTextures(textureManager, spriteManager, 33);

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        for (const auto& spriteHandle : spriteHandles)
        {
            sut.Draw(
                identity,
                materialHandle,
                spriteHandle,
                {1.0f, 1.0f},
                false,
                false
            );
        }

        sut.Flush(identity);

        EXPECT_EQ(2, renderStats.DrawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGiven32UniqueTexturesAnd1Duplicate)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const std::vector<cocoa::Graphics::SpriteHandle> spriteHandles =
            CreateSpritesWithUniqueTextures(textureManager, spriteManager, 32);

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        for (const auto& spriteHandle : spriteHandles)
        {
            sut.Draw(
                identity,
                materialHandle,
                spriteHandle,
                {1.0f, 1.0f},
                false,
                false
            );
        }

        sut.Draw(
            identity,
            materialHandle,
            spriteHandles[0],
            {1.0f, 1.0f},
            false,
            false
        );

        sut.Flush(identity);

        EXPECT_EQ(1, renderStats.DrawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGiven20000QuadsWithSameTexture)
    {
        constexpr int quadCount = 20000;
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::Math::Vector2f(0.0f, 0.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        for (auto i = 0; i < quadCount; ++i)
        {
            sut.Draw(
                identity,
                materialHandle,
                spriteHandle,
                {1.0f, 1.0f},
                false,
                false
            );
        }

        sut.Flush(identity);

        EXPECT_EQ(1, renderStats.DrawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenGiven20001QuadsWithSameTexture)
    {
        constexpr int quadCount = 20001;
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::Math::Vector2f(0.0f, 0.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        for (auto i = 0; i < quadCount; ++i)
        {
            sut.Draw(
                identity,
                materialHandle,
                spriteHandle,
                {1.0f, 1.0f},
                false,
                false
            );
        }

        sut.Flush(identity);

        EXPECT_EQ(2, renderStats.DrawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGivenSameTextureFromSpriteAndDirectTexture)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        cocoa::Graphics::MaterialManager materialManager;
        cocoa::Graphics::SpriteManager spriteManager;
        cocoa::Graphics::RenderStatistics renderStats;

        const cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::Math::Vector2f(0.0f, 0.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f),
            cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::Math::Matrix4f identity = cocoa::Math::Matrix4f::Identity();

        sut.Draw(
            identity,
            materialHandle,
            textureHandle,
            {1.0f, 1.0f}
        );
        sut.Draw(
            identity,
            materialHandle,
            spriteHandle,
            {4.0f, 2.0f},
            false,
            true
        );

        sut.Flush(identity);

        EXPECT_EQ(1, renderStats.DrawCount);
    }
}
