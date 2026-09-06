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

namespace Cocoa::Graphics::Tests
{
    static std::vector<SpriteHandle> CreateSpritesWithUniqueTextures(
        TextureManager& textureManager,
        SpriteManager& spriteManager,
        const int count)
    {
        std::vector<SpriteHandle> handles;
        constexpr uint8_t pixelData[] {255, 255, 255, 255};

        for (auto i = 0; i < count; ++i)
        {
            const TextureSpec textureSpec
            {
                .Id = "test-texture-" + std::to_string(i),
                .Width = 1,
                .Height = 1
            };

            const TextureHandle textureHandle = textureManager.Load(
                textureSpec,
                pixelData
            );

            const SpriteHandle spriteHandle = spriteManager.Load(
                "sprite-" + std::to_string(i),
                textureHandle,
                Math::Vector2f(0.0f, 0.0f),
                Math::Vector2f(1.0f, 1.0f)
            );

            handles.emplace_back(spriteHandle);
        }

        return handles;
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGivenDuplicateShaders)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        SpriteManager spriteManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 1,
            .Height = 1
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        constexpr Core::Color tint;

        const MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            tint
        );

        const MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            tint
        );

        const SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Math::Vector2f(0.0f, 0.0f),
            Math::Vector2f(1.0f, 1.0f)
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandleA, spriteHandle);
        sut.Draw(identity, materialHandleB, spriteHandle);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenShaderChanges)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        SpriteManager spriteManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandleOne = shaderManager.Load(
            "test-shader-1",
            "vertex-source",
            "fragment-source"
        );

        const ShaderHandle shaderHandleTwo = shaderManager.Load(
            "test-shader-2",
            "vertex-source",
            "fragment-source"
        );

        const TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 1,
            .Height = 1
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        constexpr Core::Color tint;

        const MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandleOne,
            tint
        );

        const MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandleTwo,
            tint
        );

        const SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Math::Vector2f(0.0f, 0.0f),
            Math::Vector2f(1.0f, 1.0f)
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandleA, spriteHandle);
        sut.Draw(identity, materialHandleB, spriteHandle);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 2);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenTextureChanges)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        SpriteManager spriteManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const TextureSpec textureSpecOne
        {
            .Id = "test-texture-01",
            .Width = 1,
            .Height = 1
        };

        const TextureSpec textureSpecTwo
        {
            .Id = "test-texture-02",
            .Width = 1,
            .Height = 1
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const TextureHandle textureHandleOne = textureManager.Load(
            textureSpecOne,
            pixelData
        );

        const TextureHandle textureHandleTwo = textureManager.Load(
            textureSpecTwo,
            pixelData
        );

        constexpr Core::Color tint;

        const MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            tint
        );

        const MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            tint
        );

        const SpriteHandle spriteHandleA = spriteManager.Load(
            "default-sprite-a",
            textureHandleOne,
            Math::Vector2f(0.0f, 0.0f),
            Math::Vector2f(1.0f, 1.0f)
        );

        const SpriteHandle spriteHandleB = spriteManager.Load(
            "default-sprite-b",
            textureHandleTwo,
            Math::Vector2f(0.0f, 0.0f),
            Math::Vector2f(1.0f, 1.0f)
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandleA, spriteHandleA);
        sut.Draw(identity, materialHandleB, spriteHandleB);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenOnlyTintChanges)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        SpriteManager spriteManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 1,
            .Height = 1
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const MaterialHandle materialHandleA = materialManager.Load(
            "material-a",
            shaderHandle,
            Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite-b",
            textureHandle,
            Math::Vector2f(0.0f, 0.0f),
            Math::Vector2f(1.0f, 1.0f)
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandleA, spriteHandle);
        sut.Draw(identity, materialHandleB, spriteHandle);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenGiven33UniqueTextures)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        SpriteManager spriteManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const std::vector<SpriteHandle> spriteHandles =
            CreateSpritesWithUniqueTextures(textureManager, spriteManager, 33);

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        for (const auto& spriteHandle : spriteHandles)
        {
            sut.Draw(identity, materialHandle, spriteHandle);
        }

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 2);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGiven32UniqueTexturesAnd1Duplicate)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        SpriteManager spriteManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        const std::vector<SpriteHandle> spriteHandles =
            CreateSpritesWithUniqueTextures(textureManager, spriteManager, 32);

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        for (const auto& spriteHandle : spriteHandles)
        {
            sut.Draw(identity, materialHandle, spriteHandle);
        }

        sut.Draw(identity, materialHandle, spriteHandles[0]);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGiven20000QuadsWithSameTexture)
    {
        constexpr int quadCount = 20000;
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        SpriteManager spriteManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 1,
            .Height = 1
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Math::Vector2f(0.0f, 0.0f),
            Math::Vector2f(1.0f, 1.0f)
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        for (auto i = 0; i < quadCount; ++i)
        {
            sut.Draw(identity, materialHandle, spriteHandle);
        }

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenGiven20001QuadsWithSameTexture)
    {
        constexpr int quadCount = 20001;
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        SpriteManager spriteManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 1,
            .Height = 1
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Math::Vector2f(0.0f, 0.0f),
            Math::Vector2f(1.0f, 1.0f)
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        for (auto i = 0; i < quadCount; ++i)
        {
            sut.Draw(identity, materialHandle, spriteHandle);
        }

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 2);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGivenSameTextureFromSpriteAndDirectTexture)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        SpriteManager spriteManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const TextureSpec textureSpec
        {
            .Id = "test-texture",
            .Width = 1,
            .Height = 1
        };

        constexpr uint8_t pixelData[]
        {
            255, 255, 255, 255
        };

        const TextureHandle textureHandle = textureManager.Load(
            textureSpec,
            pixelData
        );

        const MaterialHandle materialHandle = materialManager.Load(
            "material-a",
            shaderHandle,
            Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const SpriteHandle spriteHandle = spriteManager.Load(
            "default-sprite",
            textureHandle,
            Math::Vector2f(0.0f, 0.0f),
            Math::Vector2f(1.0f, 1.0f)
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            spriteManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandle, textureHandle);
        sut.Draw(identity, materialHandle, spriteHandle);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }
}