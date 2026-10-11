#include <Graphics/QuadBatch.hpp>
#include <Stubs/Graphics/StubGraphicsDevice.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/TextureManager.hpp>
#include <Graphics/SpriteManager.hpp>
#include <Graphics/RenderStatistics.hpp>
#include <Graphics/TextureSpec.hpp>
#include <gtest/gtest.h>

#include <vector>

namespace CocoaTests::Graphics
{
    static std::vector<Cocoa::Graphics::SpriteHandle> CreateSpritesWithUniqueTextures(
        Cocoa::Graphics::TextureManager& textureManager,
        Cocoa::Graphics::SpriteManager& spriteManager,
        const int count)
    {
        std::vector<Cocoa::Graphics::SpriteHandle> handles;
        constexpr uint8_t pixelData[] {255, 255, 255, 255};

        for (auto i = 0; i < count; ++i)
        {
            const Cocoa::Graphics::TextureSpec textureSpec
            {
                .Id = "test-texture-" + std::to_string(i),
                .Width = 256,
                .Height = 256
            };

            const Cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
                textureSpec,
                pixelData
            );

            const Cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
                "sprite-" + std::to_string(i),
                textureHandle,
                Cocoa::Math::Vector2f(0.0f, 0.0f),
                Cocoa::Math::Vector2f(256.0f, 256.0f),
                Cocoa::Math::Vector2f(256.0f, 256.0f)
            );

            handles.emplace_back(spriteHandle);
        }

        return handles;
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGivenDuplicateShaders)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const Cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        constexpr Cocoa::Core::Color tint;

        const Cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            tint
        );

        const Cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "opaque",
            tint
        );

        const Cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Cocoa::Math::Vector2f(0.0f, 0.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandleOne = shaderManager.Load(
            "test-shader-1",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::ShaderHandle shaderHandleTwo = shaderManager.Load(
            "test-shader-2",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const Cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        constexpr Cocoa::Core::Color tint;

        const Cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandleOne,
            "opaque",
            tint
        );

        const Cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandleTwo,
            "opaque",
            tint
        );

        const Cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Cocoa::Math::Vector2f(0.0f, 0.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::TextureSpec textureSpecOne
        {
            .Id = "test-texture-01",
            .Width = 256,
            .Height = 256
        };

        const Cocoa::Graphics::TextureSpec textureSpecTwo
        {
            .Id = "test-texture-02",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const Cocoa::Graphics::TextureHandle textureHandleOne = textureManager.Load(
            textureSpecOne,
            pixelData
        );

        const Cocoa::Graphics::TextureHandle textureHandleTwo = textureManager.Load(
            textureSpecTwo,
            pixelData
        );

        constexpr Cocoa::Core::Color tint;

        const Cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            tint
        );

        const Cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "opaque",
            tint
        );

        const Cocoa::Graphics::SpriteHandle spriteHandleA = spriteManager.Load(
            "default-sprite-a",
            textureHandleOne,
            Cocoa::Math::Vector2f(0.0f, 0.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        const Cocoa::Graphics::SpriteHandle spriteHandleB = spriteManager.Load(
            "default-sprite-b",
            textureHandleTwo,
            Cocoa::Math::Vector2f(0.0f, 0.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const Cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const Cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            Cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const Cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "opaque",
            Cocoa::Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const Cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite-b",
            textureHandle,
            Cocoa::Math::Vector2f(0.0f, 0.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const Cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const Cocoa::Graphics::MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            Cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const Cocoa::Graphics::MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            "alpha",
            Cocoa::Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const Cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite-b",
            textureHandle,
            Cocoa::Math::Vector2f(0.0f, 0.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            Cocoa::Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const std::vector<Cocoa::Graphics::SpriteHandle> spriteHandles =
            CreateSpritesWithUniqueTextures(textureManager, spriteManager, 33);

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            Cocoa::Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const std::vector<Cocoa::Graphics::SpriteHandle> spriteHandles =
            CreateSpritesWithUniqueTextures(textureManager, spriteManager, 32);

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const Cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const Cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            Cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const Cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Cocoa::Math::Vector2f(0.0f, 0.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const Cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const Cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            Cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const Cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Cocoa::Math::Vector2f(0.0f, 0.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::TextureManager textureManager(graphicsDevice);
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::SpriteManager spriteManager;
        Cocoa::Graphics::RenderStatistics renderStats;

        const Cocoa::Graphics::ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const Cocoa::Graphics::TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 256,
            .Height = 256
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const Cocoa::Graphics::TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const Cocoa::Graphics::MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            "opaque",
            Cocoa::Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const Cocoa::Graphics::SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Cocoa::Math::Vector2f(0.0f, 0.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f),
            Cocoa::Math::Vector2f(256.0f, 256.0f)
        );

        Cocoa::Graphics::QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Cocoa::Math::Matrix4f identity = Cocoa::Math::Matrix4f::Identity();

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