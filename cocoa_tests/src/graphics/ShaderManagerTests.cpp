#include "stubs/graphics/StubGraphicsDevice.hpp"
#include "stubs/graphics/StubShader.hpp"
#include <graphics/GraphicsHandles.hpp>
#include <graphics/ShaderManager.hpp>

#include <gtest/gtest.h>
#include <stdexcept>

namespace cocoa_tests::graphics
{
    TEST(ShaderManagerTests, Load_ShouldReturnShaderHandle_WhenProvidingValidValues)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::graphics::ShaderHandle result = sut.Load("1", "default", "default");

        EXPECT_EQ(result.Id, 1);
    }

    TEST(ShaderManagerTests, Load_ShouldReturnSameShaderHandleId_WhenProvidingSameShaderIds)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::graphics::ShaderHandle result1 = sut.Load("1", "default", "default");
        cocoa::graphics::ShaderHandle result2 = sut.Load("1", "default", "default");

        EXPECT_EQ(result1.Id, result2.Id);
    }

    TEST(ShaderManagerTests, Load_ShouldNotReturnSameShaderHandleId_WhenProvidingUniqueShaderId)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::graphics::ShaderHandle result1 = sut.Load("1", "default", "default");
        cocoa::graphics::ShaderHandle result2 = sut.Load("2", "default", "default");

        EXPECT_NE(result1.Id, result2.Id);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnShader_WhenProvidingValidHandle)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::graphics::ShaderHandle handle = sut.Load("1", "default", "default");
        const cocoa::graphics::Shader& shader = sut.Get(handle);

        EXPECT_NE(&shader, nullptr);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnDifferentShader_WhenProvidingDifferentHandles)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::graphics::ShaderHandle handle1 = sut.Load("1", "default", "default");
        cocoa::graphics::ShaderHandle handle2 = sut.Load("2", "value", "value");
        const cocoa::graphics::Shader& shader1 = sut.Get(handle1);
        const cocoa::graphics::Shader& shader2 = sut.Get(handle2);

        EXPECT_NE(&shader1, &shader2);
    }

    TEST(ShaderManagerTests, Get_ShouldReturnSameShader_WhenProvidingSameHandle)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::graphics::ShaderHandle handle = sut.Load("1", "default", "default");
        const cocoa::graphics::Shader& shader1 = sut.Get(handle);
        const cocoa::graphics::Shader& shader2 = sut.Get(handle);

        EXPECT_EQ(&shader1, &shader2);
    }

    TEST(ShaderManagerTests, Get_ShouldThrowError_WhenProvidingMissingHandle)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::ShaderManager sut(stubGraphicsDevice);

        cocoa::graphics::ShaderHandle handle{ .Id = 9999 };

        EXPECT_THROW(
            {
                sut.Get(handle);
            },
            std::runtime_error
        );
    }

    TEST(ShaderManagerTests, TryGetHandle_ShouldReturnTrueAndOutHandle_WhenIdExists)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::ShaderManager sut(stubGraphicsDevice);
        const std::string shaderId = "1";
        cocoa::graphics::ShaderHandle expectedHandle = sut.Load(shaderId, "default", "default");

        cocoa::graphics::ShaderHandle outHandle;
        bool result = sut.TryGetHandle(shaderId, outHandle);

        EXPECT_TRUE(result);
        EXPECT_EQ(outHandle.Id, expectedHandle.Id);
    }

    TEST(ShaderManagerTests, TryGetHandle_ShouldReturnFalseAndOutHandle_WhenIdDoesNotExist)
    {
        stubs::StubGraphicsDevice stubGraphicsDevice;
        cocoa::graphics::ShaderManager sut(stubGraphicsDevice);
        sut.Load("1", "default", "default");

        cocoa::graphics::ShaderHandle outHandle;
        bool result = sut.TryGetHandle("badId", outHandle);

        EXPECT_FALSE(result);
        EXPECT_EQ(outHandle.Id, 0);
    }
}
