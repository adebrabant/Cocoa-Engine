#include <Graphics/CircleBatch.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/RenderStatistics.hpp>
#include <gtest/gtest.h>

#include "Stubs/Graphics/StubGraphicsDevice.hpp"

namespace CocoaTests::Graphics
{
    struct CircleBatchScenario
    {
        int MaxSubmissionCount;
        int ExpectDrawCount;
        std::string ScenarioName;
    };

    class CircleBatchDrawCountTests : public testing::TestWithParam<CircleBatchScenario> { };

    INSTANTIATE_TEST_SUITE_P(
        CircleBatchDrawCountValues,
        CircleBatchDrawCountTests,
        testing::Values(
            CircleBatchScenario
            {
                .MaxSubmissionCount = 1,
                .ExpectDrawCount = 1,
                .ScenarioName = "Single Submission"
            },
            CircleBatchScenario
            {
                .MaxSubmissionCount = 20001,
                .ExpectDrawCount = 2,
                .ScenarioName = "Max Submission"
            }
        )
    );

    TEST_P(CircleBatchDrawCountTests, Flush_ShouldDrawExpectedCount_WhenGivenScenario)
    {
        const CircleBatchScenario& scenario = GetParam();

        Stubs::StubGraphicsDevice graphicsDevice;
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::RenderStatistics renderStats;
        Cocoa::Graphics::CircleBatch sut(
            graphicsDevice,
            materialManager,
            shaderManager,
            renderStats
        );

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

        constexpr auto identity = Cocoa::Math::Matrix4f::Identity();
        constexpr auto color = Cocoa::Math::Vector4f(1.0, 0.0, 1.0, 1.0);

        for (int i = 0; i < scenario.MaxSubmissionCount; ++i)
        {
            sut.Draw(identity, materialHandle, color,0.5f,0.5f);
        }

        sut.Flush(identity);

        EXPECT_EQ(scenario.ExpectDrawCount, renderStats.DrawCount);
    }
}