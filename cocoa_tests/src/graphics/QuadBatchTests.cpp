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
                .id = "test-texture-" + std::to_string(i),
                .width = 256,
                .height = 256
            };

            const cocoa::graphics::TextureHandle textureHandle = textureManager.load(
                textureSpec,
                pixelData
            );

            const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.load(
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

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .id = "test-texture",
            .width = 256,
            .height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.load(
            textureSpec,
            pixelData
        );

        constexpr cocoa::core::Color tint;

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.load(
            "material-a",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.load(
            "material-b",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        sut.draw(
            identity,
            materialHandleA,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.draw(
            identity,
            materialHandleB,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.flush(identity);

        EXPECT_EQ(1, renderStats.drawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenShaderChanges)
    {
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandleOne = shaderManager.load(
            "test-shader-1",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::ShaderHandle shaderHandleTwo = shaderManager.load(
            "test-shader-2",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .id = "test-texture",
            .width = 256,
            .height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.load(
            textureSpec,
            pixelData
        );

        constexpr cocoa::core::Color tint;

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.load(
            "material-a",
            shaderHandleOne,
            "opaque",
            tint
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.load(
            "material-b",
            shaderHandleTwo,
            "opaque",
            tint
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        sut.draw(
            identity,
            materialHandleA,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.draw(
            identity,
            materialHandleB,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.flush(identity);

        EXPECT_EQ(2, renderStats.drawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenTextureChanges)
    {
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpecOne
        {
            .id = "test-texture-01",
            .width = 256,
            .height = 256
        };

        const cocoa::graphics::TextureSpec textureSpecTwo
        {
            .id = "test-texture-02",
            .width = 256,
            .height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandleOne = textureManager.load(
            textureSpecOne,
            pixelData
        );

        const cocoa::graphics::TextureHandle textureHandleTwo = textureManager.load(
            textureSpecTwo,
            pixelData
        );

        constexpr cocoa::core::Color tint;

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.load(
            "material-a",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.load(
            "material-b",
            shaderHandle,
            "opaque",
            tint
        );

        const cocoa::graphics::SpriteHandle spriteHandleA = spriteManager.load(
            "default-sprite-a",
            textureHandleOne,
            cocoa::math::Vector2f(0.0f, 0.0f),
            cocoa::math::Vector2f(256.0f, 256.0f),
            cocoa::math::Vector2f(256.0f, 256.0f)
        );

        const cocoa::graphics::SpriteHandle spriteHandleB = spriteManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        sut.draw(
            identity,
            materialHandleA,
            spriteHandleA,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.draw(
            identity,
            materialHandleB,
            spriteHandleB,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.flush(identity);

        EXPECT_EQ(1, renderStats.drawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenOnlyTintChanges)
    {
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .id = "test-texture",
            .width = 256,
            .height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.load(
            "material-b",
            shaderHandle,
            "opaque",
            cocoa::core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        sut.draw(
            identity,
            materialHandleA,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.draw(
            identity,
            materialHandleB,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.flush(identity);

        EXPECT_EQ(1, renderStats.drawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenGivenDifferentBlendMode)
    {
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .id = "test-texture",
            .width = 256,
            .height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandleA = materialManager.load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::MaterialHandle materialHandleB = materialManager.load(
            "material-b",
            shaderHandle,
            "alpha",
            cocoa::core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        sut.draw(
            identity,
            materialHandleA,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );
        sut.draw(
            identity,
            materialHandleB,
            spriteHandle,
            {1.0f, 1.0f},
            false,
            false
        );

        sut.flush(identity);

        EXPECT_EQ(2, renderStats.drawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenGiven33UniqueTextures)
    {
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        for (const auto& spriteHandle : spriteHandles)
        {
            sut.draw(
                identity,
                materialHandle,
                spriteHandle,
                {1.0f, 1.0f},
                false,
                false
            );
        }

        sut.flush(identity);

        EXPECT_EQ(2, renderStats.drawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGiven32UniqueTexturesAnd1Duplicate)
    {
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        for (const auto& spriteHandle : spriteHandles)
        {
            sut.draw(
                identity,
                materialHandle,
                spriteHandle,
                {1.0f, 1.0f},
                false,
                false
            );
        }

        sut.draw(
            identity,
            materialHandle,
            spriteHandles[0],
            {1.0f, 1.0f},
            false,
            false
        );

        sut.flush(identity);

        EXPECT_EQ(1, renderStats.drawCount);
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

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .id = "test-texture",
            .width = 256,
            .height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        for (auto i = 0; i < quadCount; ++i)
        {
            sut.draw(
                identity,
                materialHandle,
                spriteHandle,
                {1.0f, 1.0f},
                false,
                false
            );
        }

        sut.flush(identity);

        EXPECT_EQ(1, renderStats.drawCount);
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

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .id = "test-texture",
            .width = 256,
            .height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        for (auto i = 0; i < quadCount; ++i)
        {
            sut.draw(
                identity,
                materialHandle,
                spriteHandle,
                {1.0f, 1.0f},
                false,
                false
            );
        }

        sut.flush(identity);

        EXPECT_EQ(2, renderStats.drawCount);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGivenSameTextureFromSpriteAndDirectTexture)
    {
        stubs::StubGraphicsDevice graphicsDevice;
        cocoa::graphics::ShaderManager shaderManager(graphicsDevice);
        cocoa::graphics::TextureManager textureManager(graphicsDevice);
        cocoa::graphics::MaterialManager materialManager;
        cocoa::graphics::SpriteManager spriteManager;
        cocoa::graphics::RenderStatistics renderStats;

        const cocoa::graphics::ShaderHandle shaderHandle = shaderManager.load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const cocoa::graphics::TextureSpec textureSpec
        {
            .id = "test-texture",
            .width = 256,
            .height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const cocoa::graphics::TextureHandle textureHandle = textureManager.load(
            textureSpec,
            pixelData
        );

        const cocoa::graphics::MaterialHandle materialHandle = materialManager.load(
            "material-a",
            shaderHandle,
            "opaque",
            cocoa::core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const cocoa::graphics::SpriteHandle spriteHandle = spriteManager.load(
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

        constexpr cocoa::math::Matrix4f identity = cocoa::math::Matrix4f::identity();

        sut.draw(
            identity,
            materialHandle,
            textureHandle,
            {1.0f, 1.0f}
        );
        sut.draw(
            identity,
            materialHandle,
            spriteHandle,
            {4.0f, 2.0f},
            false,
            true
        );

        sut.flush(identity);

        EXPECT_EQ(1, renderStats.drawCount);
    }
}
