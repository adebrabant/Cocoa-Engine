#include <graphics/MaterialManager.hpp>
#include <graphics/QuadBatch.hpp>
#include <graphics/RenderStatistics.hpp>
#include <graphics/ShaderManager.hpp>
#include <graphics/SpriteManager.hpp>
#include <graphics/TextureManager.hpp>
#include <graphics/TextureSpec.hpp>
#include <gtest/gtest.h>
#include <stubs/graphics/StubGraphicsDevice.hpp>

#include <vector>

namespace cocoa_tests::graphics
{
    static std::vector<cocoa::graphics::SpriteHandle> CreateSpritesWithUniqueTextures(
        cocoa::graphics::TextureManager& textureManager,
        cocoa::graphics::SpriteManager& spriteManager,
        const int count)
    {
        std::vector<cocoa::graphics::SpriteHandle> handles;
        constexpr uint8_t pixelData[] {255, 255, 255, 255};

        for (auto i = 0; i < count; ++i)
        {
            const cocoa::graphics::TextureSpec textureSpec
            {
                .Id = "test-texture-" + std::to_string(i),
                .Width = 256,
                .Height = 256
            };

            const cocoa::graphics::TextureHandle textureHandle = textureManager.Load(
                textureSpec,
                pixelData
            );

            const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.Load(
                "sprite-" + std::to_string(i),
                textureHandle,
                cocoa::math::Vector2f(0.0f, 0.0f),
                cocoa::math::Vector2f(256.0f, 256.0f),
                cocoa::math::Vector2f(256.0f, 256.0f)
            );

            handles.emplace_back(spriteHandle);
        }

        return handles;
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGivenDuplicateShaders)
    {
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        constexpr cocoa::core::Color tint;

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandleOne = shaderManager.Load(
            "test-shader-1",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::ShaderHandle shaderHandleTwo = shaderManager.Load(
            "test-shader-2",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        constexpr cocoa::core::Color tint;

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandleOne,
            "opaque",
            tint
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandleTwo,
            "opaque",
            tint
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpecOne
        {
            .Id = "test-texture-01",
            .Width = 256,
            .Height = 256
        };

        const cocoa::graphics::TextureSpec textureSpecTwo
        {
            .Id = "test-texture-02",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandleOne = textureManager.Load(
            textureSpecOne,
            pixelData
        );

        const cocoa::graphics::TextureHandle textureHandleTwo = textureManager.Load(
            textureSpecTwo,
            pixelData
        );

        constexpr cocoa::core::Color tint;

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::graphics::SpriteHandle spriteHandleA = spriteManager.Load(
            "default-sprite-a",
            textureHandleOne,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        const cocoa::graphics::SpriteHandle spriteHandleB = spriteManager.Load(
            "default-sprite-b",
            textureHandleTwo,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "opaque",
            cocoa::core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite-b",
            textureHandle,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "alpha",
            cocoa::core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite-b",
            textureHandle,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const std::vector<cocoa::graphics::SpriteHandle> spriteHandles =
            CreateSpritesWithUniqueTextures(textureManager, spriteManager, 33);

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const std::vector<cocoa::graphics::SpriteHandle> spriteHandles =
            CreateSpritesWithUniqueTextures(textureManager, spriteManager, 32);

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        cocoa::graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::Identity();

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
