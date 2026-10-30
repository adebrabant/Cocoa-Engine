#include "stubs/Graphics/StubGraphicsDevice.hpp"
#include "stubs/Graphics/StubShader.hpp"
#include <graphics/GraphicsHandles.hpp>
#include <graphics/ShaderManager.hpp>

#include <gtest/gtest.h>
#include <stdexcept>

namespace CocoaTests::Graphics
{
    TEST(ShaderManagerTests, Load_ShouldReturnShaderHandle_WhenProvidingValidValues)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::Graphics::ShaderHandle result = sut.Load("1", "default", "default");

        EXPECT_EQ(result.Id, 1);
    }

    TEST(ShaderManagerTests, Load_ShouldReturnSameShaderHandleId_WhenProvidingSameShaderIds)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::Graphics::ShaderHandle result1 = sut.Load("1", "default", "default");
        cocoa::Graphics::ShaderHandle result2 = sut.Load("1", "default", "default");

        EXPECT_EQ(result1.Id, result2.Id);
    }

    TEST(ShaderManagerTests, Load_ShouldNotReturnSameShaderHandleId_WhenProvidingUniqueShaderId)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::Graphics::ShaderHandle result1 = sut.Load("1", "default", "default");
        cocoa::Graphics::ShaderHandle result2 = sut.Load("2", "default", "default");

        EXPECT_NE(result1.Id, result2.Id);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnShader_WhenProvidingValidHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::Graphics::ShaderHandle handle = sut.Load("1", "default", "default");
        const cocoa::Graphics::Shader& shader = sut.Get(handle);

        EXPECT_NE(&shader, nullptr);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnDifferentShader_WhenProvidingDifferentHandles)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::Graphics::ShaderHandle handle1 = sut.Load("1", "default", "default");
        cocoa::Graphics::ShaderHandle handle2 = sut.Load("2", "value", "value");
        const cocoa::Graphics::Shader& shader1 = sut.Get(handle1);
        const cocoa::Graphics::Shader& shader2 = sut.Get(handle2);

        EXPECT_NE(&shader1, &shader2);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnSameShader_WhenProvidingSameHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::Graphics::ShaderHandle handle = sut.Load("1", "default", "default");
        const cocoa::Graphics::Shader& shader1 = sut.Get(handle);
        const cocoa::Graphics::Shader& shader2 = sut.Get(handle);

        EXPECT_EQ(&shader1, &shader2);
    }

    TEST(ShaderManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::Graphics::ShaderHandle handle{ .Id = 9999 };

        EXPECT_THROW(
            {
                sut.Get(handle);
            },
            std::runtime_error
        );
    }

    TEST(ShaderManagerTests, TryGetHandle_ShouldReturnTrueAndOutHandle_WhenIdExists)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);
        const std::string shaderId = "1";
        cocoa::Graphics::ShaderHandle expectedHandle = sut.Load(shaderId, "default", "default");

        cocoa::Graphics::ShaderHandle outHandle;
        bool result = sut.TryGetHandle(shaderId, outHandle);

        EXPECT_TRUE(result);
        EXPECT_EQ(outHandle.Id, expectedHandle.Id);
    }

    TEST(ShaderManagerTests, TryGetHandle_ShouldReturnFalseAndOutHandle_WhenIdDoesNotExist)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);
        sut.Load("1", "default", "default");

        cocoa::Graphics::ShaderHandle outHandle;
        bool result = sut.TryGetHandle("badId", outHandle);

        EXPECT_FALSE(result);
        EXPECT_EQ(outHandle.Id, 0);
    }
}