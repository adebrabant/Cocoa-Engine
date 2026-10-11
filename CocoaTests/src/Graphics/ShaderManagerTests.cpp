#include "Stubs/Graphics/StubGraphicsDevice.hpp"
#include "Stubs/Graphics/StubShader.hpp"
#include <Graphics/ShaderManager.hpp>
#include <Graphics/GraphicsHandles.hpp>

#include <gtest/gtest.h>
#include <stdexcept>

namespace CocoaTests::Graphics
{
    TEST(ShaderManagerTests, Load_ShouldReturnShaderHandle_WhenProvidingValidValues)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        Cocoa::Graphics::ShaderHandle result = sut.Load("1", "default", "default");

        EXPECT_EQ(result.Id, 1);
    }

    TEST(ShaderManagerTests, Load_ShouldReturnSameShaderHandleId_WhenProvidingSameShaderIds)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        Cocoa::Graphics::ShaderHandle result1 = sut.Load("1", "default", "default");
        Cocoa::Graphics::ShaderHandle result2 = sut.Load("1", "default", "default");

        EXPECT_EQ(result1.Id, result2.Id);
    }

    TEST(ShaderManagerTests, Load_ShouldNotReturnSameShaderHandleId_WhenProvidingUniqueShaderId)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        Cocoa::Graphics::ShaderHandle result1 = sut.Load("1", "default", "default");
        Cocoa::Graphics::ShaderHandle result2 = sut.Load("2", "default", "default");

        EXPECT_NE(result1.Id, result2.Id);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnShader_WhenProvidingValidHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        Cocoa::Graphics::ShaderHandle handle = sut.Load("1", "default", "default");
        const Cocoa::Graphics::Shader& shader = sut.Get(handle);

        EXPECT_NE(&shader, nullptr);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnDifferentShader_WhenProvidingDifferentHandles)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        Cocoa::Graphics::ShaderHandle handle1 = sut.Load("1", "default", "default");
        Cocoa::Graphics::ShaderHandle handle2 = sut.Load("2", "value", "value");
        const Cocoa::Graphics::Shader& shader1 = sut.Get(handle1);
        const Cocoa::Graphics::Shader& shader2 = sut.Get(handle2);

        EXPECT_NE(&shader1, &shader2);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnSameShader_WhenProvidingSameHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        Cocoa::Graphics::ShaderHandle handle = sut.Load("1", "default", "default");
        const Cocoa::Graphics::Shader& shader1 = sut.Get(handle);
        const Cocoa::Graphics::Shader& shader2 = sut.Get(handle);

        EXPECT_EQ(&shader1, &shader2);
    }

    TEST(ShaderManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);

        Cocoa::Graphics::ShaderHandle handle{ .Id = 9999 };

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
        Cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);
        const std::string shaderId = "1";
        Cocoa::Graphics::ShaderHandle expectedHandle = sut.Load(shaderId, "default", "default");

        Cocoa::Graphics::ShaderHandle outHandle;
        bool result = sut.TryGetHandle(shaderId, outHandle);

        EXPECT_TRUE(result);
        EXPECT_EQ(outHandle.Id, expectedHandle.Id);
    }

    TEST(ShaderManagerTests, TryGetHandle_ShouldReturnFalseAndOutHandle_WhenIdDoesNotExist)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Cocoa::Graphics::ShaderManager sut(stubGraphicsDevice);
        sut.Load("1", "default", "default");

        Cocoa::Graphics::ShaderHandle outHandle;
        bool result = sut.TryGetHandle("badId", outHandle);

        EXPECT_FALSE(result);
        EXPECT_EQ(outHandle.Id, 0);
    }
}