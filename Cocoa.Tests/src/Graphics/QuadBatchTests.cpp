#include <Graphics/QuadBatch.hpp>
#include <Stubs/Graphics/StubGraphicsDevice.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/TextureManager.hpp>
#include <Graphics/RenderStatistics.hpp>
#include <Graphics/TextureSpec.hpp>
#include <gtest/gtest.h>

namespace Cocoa::Graphics::Tests
{
    static std::vector<MaterialHandle> CreateMaterialsWithUniqueTextures(
        TextureManager& textureManager,
        MaterialManager& materialManager,
        const ShaderHandle& shaderHandle,
        const int count)
    {
        std::vector<MaterialHandle> handles;
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

            const MaterialHandle materialHandle = materialManager.Load(
                "material-" + std::to_string(i),
                shaderHandle,
                textureHandle,
                Core::Color{0.5, 1.0, 0.5, 1.0f}
            );

            handles.emplace_back(materialHandle);
        }

        return handles;
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGivenDuplicateShaders)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
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
            textureHandle,
            tint
        );

        const MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            textureHandle,
            tint
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandleA);
        sut.Draw(identity, materialHandleB);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenShaderChanges)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
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
            textureHandle,
            tint
        );

        const MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandleTwo,
            textureHandle,
            tint
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandleA);
        sut.Draw(identity, materialHandleB);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 2);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenTextureChanges)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
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
            textureHandleOne,
            tint
        );

        const MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            textureHandleTwo,
            tint
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandleA);
        sut.Draw(identity, materialHandleB);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenOnlyTintChanges)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
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
            textureHandle,
            Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        const MaterialHandle materialHandleB = materialManager.Load(
            "material-b",
            shaderHandle,
            textureHandle,
            Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandleA);
        sut.Draw(identity, materialHandleB);

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenGiven33UinqueTextures)
    {
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const std::vector<MaterialHandle> materialHandles =
            CreateMaterialsWithUniqueTextures(textureManager, materialManager, shaderHandle, 33);

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        for (const auto& materialHandle : materialHandles)
        {
            sut.Draw(identity, materialHandle);
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
        RenderStatistics renderStats;

        const ShaderHandle shaderHandle = shaderManager.Load(
            "test-shader",
            "vertex-source",
            "fragment-source"
        );

        const std::vector<MaterialHandle> materialHandles =
            CreateMaterialsWithUniqueTextures(textureManager, materialManager, shaderHandle, 32);

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        sut.Draw(identity, materialHandles[0]);

        for (const auto& materialHandle : materialHandles)
        {
            sut.Draw(identity, materialHandle);
        }

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawOnce_WhenGiven20000DuplicateTextures)
    {
        constexpr int m_drawCount = 20000;
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
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
            textureHandle,
            Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        for (auto i = 0; i < m_drawCount; ++i)
        {
            sut.Draw(identity, materialHandle);
        }

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 1);
    }

    TEST(QuadBatchTests, Flush_ShouldDrawTwice_WhenGiven20001DuplicateTextures)
    {
        constexpr int m_drawCount = 20001;
        Stubs::StubGraphicsDevice graphicsDevice;
        ShaderManager shaderManager(graphicsDevice);
        TextureManager textureManager(graphicsDevice);
        MaterialManager materialManager;
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
            textureHandle,
            Core::Color{0.5, 1.0, 0.5, 1.0f}
        );

        QuadBatch sut(
            graphicsDevice,
            shaderManager,
            textureManager,
            materialManager,
            renderStats
        );

        constexpr Math::Matrix4f identity = Math::Matrix4f::Identity();

        for (auto i = 0; i < m_drawCount; ++i)
        {
            sut.Draw(identity, materialHandle);
        }

        sut.Flush(identity);

        EXPECT_EQ(renderStats.DrawCount, 2);
    }
}