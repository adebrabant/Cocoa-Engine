#include <Graphics/CircleBatch.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/RenderStatistics.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "Stubs/Graphics/StubGraphicsDevice.hpp"

namespace CocoaTests::Graphics
{
    struct MaterialTestData
    {
        std::string ShaderId;
        std::string BlendMode;
    };
    struct CircleBatchScenario
    {
        int MaxSubmissionCount;
        std::vector<MaterialTestData> MaterialTestDatas;
        int ExpectDrawCount;
        int ExpectBatchFlushCount;
        std::string ScenarioName;
    };

    class CircleBatchDrawCountTests : public testing::TestWithParam<CircleBatchScenario> { };

    INSTANTIATE_TEST_SUITE_P(
        CircleBatchDrawCountValues,
        CircleBatchDrawCountTests,
        testing::Values(
           CircleBatchScenario
            {
                .MaxSubmissionCount = 0,
                .ExpectDrawCount = 0,
                .ExpectBatchFlushCount = 0,
                .ScenarioName = "No Submission"
            },
            CircleBatchScenario
            {
                .MaxSubmissionCount = 1,
                .MaterialTestDatas = {
                    MaterialTestData{ .ShaderId = "test-shader", .BlendMode = "opaque" }
                },
                .ExpectDrawCount = 1,
                .ExpectBatchFlushCount = 1,
                .ScenarioName = "Single Submission"
            },
            CircleBatchScenario
            {
                .MaxSubmissionCount = 20001,
                .MaterialTestDatas = {
                    MaterialTestData{ .ShaderId = "test-shader", .BlendMode = "opaque" }
                },
                .ExpectDrawCount = 2,
                .ExpectBatchFlushCount = 1,
                .ScenarioName = "Max Submission"
            },
            CircleBatchScenario
            {
                .MaxSubmissionCount = 2,
                .MaterialTestDatas = {
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "opaque" },
                    MaterialTestData { .ShaderId = "shader-b", .BlendMode = "opaque" }
                },
                .ExpectDrawCount = 2,
                .ExpectBatchFlushCount = 1,
                .ScenarioName = "Different Shaders Submission"
            },
            CircleBatchScenario
            {
                .MaxSubmissionCount = 3,
                .MaterialTestDatas = {
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "opaque" },
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "additive" },
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "reversesubtract" },
                },
                .ExpectDrawCount = 3,
                .ExpectBatchFlushCount = 1,
                .ScenarioName = "Different BlendModes Submission"
            },
            CircleBatchScenario
            {
                .MaxSubmissionCount = 21000,
                .MaterialTestDatas = {
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "opaque" },
                    MaterialTestData { .ShaderId = "shader-b", .BlendMode = "opaque" },
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "additive" },
                },
                .ExpectDrawCount = 4,
                .ExpectBatchFlushCount = 1,
                .ScenarioName = "Mix Submission"
            }
        )
    );

    TEST_P(CircleBatchDrawCountTests, Flush_ShouldProcessDrawCommands_WhenGivenScenario)
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

        std::vector<Cocoa::Graphics::MaterialHandle> materialHandles{};
        materialHandles.reserve(scenario.MaterialTestDatas.size());
        for (auto i = 0; i < scenario.MaterialTestDatas.size(); ++i)
        {
            auto shaderHandle = shaderManager.Load(
                scenario.MaterialTestDatas[i].ShaderId,
                "vertex-source",
                "fragment-source"
            );
            auto materialHandle = materialManager.Load(
                "material-" + std::to_string(i),
                shaderHandle,
                scenario.MaterialTestDatas[i].BlendMode,
                Cocoa::Core::Color{1.0f, 1.0f, 1.0f, 1.0f}
            );

            materialHandles.emplace_back(materialHandle);
        }

        constexpr auto identity = Cocoa::Math::Matrix4f::Identity();
        constexpr auto color = Cocoa::Math::Vector4f(1.0, 0.0, 1.0, 1.0);
        int materialHandleCounter{0};

        for (int i = 0; i < scenario.MaxSubmissionCount; ++i)
        {
            sut.Draw(
                identity,
                materialHandles[materialHandleCounter],
                color,
                0.5f,
                0.5f
            );

            if (materialHandleCounter < materialHandles.size() - 1)
            {
                materialHandleCounter++;
            }
        }

        sut.Flush(identity);

        EXPECT_EQ(scenario.ExpectDrawCount, renderStats.DrawCount);
        EXPECT_EQ(scenario.ExpectBatchFlushCount, renderStats.BatchFlushCount);
    }
}