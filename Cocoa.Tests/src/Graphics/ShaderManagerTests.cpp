#include "Stubs/Graphics/StubGraphicsDevice.hpp"
#include "Stubs/Graphics/StubShader.hpp"
#include <Graphics/ShaderManager.hpp>
#include <gtest/gtest.h>
#include <stdexcept>

namespace Cocoa::Graphics::Tests
{
    TEST(ShaderManagerTests, Load_ShouldReturnShaderHandle_WhenProvidingValidValues)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::ShaderManager sut(stubGraphicsDevice);

        ShaderHandle result = sut.Load("1", "default", "default");

        EXPECT_EQ(result.Id, 1);
    }

    TEST(ShaderManagerTests, Load_ShouldReturnSameShaderHandleId_WhenProvidingSameShaderIds)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::ShaderManager sut(stubGraphicsDevice);

        ShaderHandle result1 = sut.Load("1", "default", "default");
        ShaderHandle result2 = sut.Load("1", "default", "default");

        EXPECT_EQ(result1.Id, result2.Id);
    }

    TEST(ShaderManagerTests, Load_ShouldNotReturnSameShaderHandleId_WhenProvidingUniqueShaderId)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::ShaderManager sut(stubGraphicsDevice);

        ShaderHandle result1 = sut.Load("1", "default", "default");
        ShaderHandle result2 = sut.Load("2", "default", "default");

        EXPECT_NE(result1.Id, result2.Id);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnShader_WhenProvidingValidHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::ShaderManager sut(stubGraphicsDevice);

        ShaderHandle handle = sut.Load("1", "default", "default");
        const Graphics::Shader& shader = sut.Get(handle);

        EXPECT_NE(&shader, nullptr);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnDifferentShader_WhenProvidingDifferentHandles)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::ShaderManager sut(stubGraphicsDevice);

        ShaderHandle handle1 = sut.Load("1", "default", "default");
        ShaderHandle handle2 = sut.Load("2", "value", "value");
        const Graphics::Shader& shader1 = sut.Get(handle1);
        const Graphics::Shader& shader2 = sut.Get(handle2);

        EXPECT_NE(&shader1, &shader2);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnSameShader_WhenProvidingSameHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::ShaderManager sut(stubGraphicsDevice);

        ShaderHandle handle = sut.Load("1", "default", "default");
        const Graphics::Shader& shader1 = sut.Get(handle);
        const Graphics::Shader& shader2 = sut.Get(handle);

        EXPECT_EQ(&shader1, &shader2);
    }

    TEST(ShaderManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
    {
        Stubs::StubGraphicsDevice stubGraphicsDevice;
        Graphics::ShaderManager sut(stubGraphicsDevice);

        ShaderHandle handle{ .Id = 9999 };

        EXPECT_THROW(
            {
                sut.Get(handle);
            },
            std::runtime_error
        );
    }
}