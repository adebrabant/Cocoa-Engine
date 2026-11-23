#include <Graphics/LineBatch.hpp>
#include "Stubs/Graphics/StubGraphicsDevice.hpp"
#include <Graphics/MaterialManager.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/RenderStatistics.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace CocoaTests::Graphics
{
    struct MaterialTestData
    {
        std::string ShaderId;
        std::string BlendMode;
    };

    struct LineBatchScenario
    {
        int MaxSubmissionCount;
        std::vector<MaterialTestData> MaterialTestDatas;
        int ExpectedDrawCount;
        int ExpectedBatchFlushCount;
        std::string ScenarioName;
    };

    class LineBatchDrawCountTests : public testing::TestWithParam<LineBatchScenario> { };

    INSTANTIATE_TEST_SUITE_P(
        LineBatchDrawCountValues,
        LineBatchDrawCountTests,
        testing::Values(
        LineBatchScenario
            {
                .MaxSubmissionCount = 0,
                .ExpectedDrawCount = 0,
                .ExpectedBatchFlushCount = 0,
                .ScenarioName = "No Submission"
            },
            LineBatchScenario
            {
                .MaxSubmissionCount = 1,
                .MaterialTestDatas = {
                    MaterialTestData{ .ShaderId = "test-shader", .BlendMode = "opaque" }
                },
                .ExpectedDrawCount = 1,
                .ExpectedBatchFlushCount = 1,
                .ScenarioName = "Single Submission"
            },
            LineBatchScenario
            {
                .MaxSubmissionCount = 20001,
                .MaterialTestDatas = {
                    MaterialTestData{ .ShaderId = "test-shader", .BlendMode = "opaque" }
                },
                .ExpectedDrawCount = 2,
                .ExpectedBatchFlushCount = 1,
                .ScenarioName = "Max Submission"
            },
            LineBatchScenario
            {
                .MaxSubmissionCount = 2,
                .MaterialTestDatas = {
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "opaque" },
                    MaterialTestData { .ShaderId = "shader-b", .BlendMode = "opaque" }
                },
                .ExpectedDrawCount = 2,
                .ExpectedBatchFlushCount = 1,
                .ScenarioName = "Different Shaders Submission"
            },
            LineBatchScenario
            {
                .MaxSubmissionCount = 3,
                .MaterialTestDatas = {
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "opaque" },
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "additive" },
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "reversesubtract" },
                },
                .ExpectedDrawCount = 3,
                .ExpectedBatchFlushCount = 1,
                .ScenarioName = "Different BlendModes Submission"
            },
            LineBatchScenario
            {
                .MaxSubmissionCount = 21000,
                .MaterialTestDatas = {
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "opaque" },
                    MaterialTestData { .ShaderId = "shader-b", .BlendMode = "opaque" },
                    MaterialTestData { .ShaderId = "shader-a", .BlendMode = "additive" },
                },
                .ExpectedDrawCount = 4,
                .ExpectedBatchFlushCount = 1,
                .ScenarioName = "Mix Submission"
            }
        )
    );

    TEST_P(LineBatchDrawCountTests, Flush_ShouldProcessDrawCommands_WhenGivenScenario)
    {
        const LineBatchScenario& scenario = GetParam();
        Stubs::StubGraphicsDevice graphicsDevice;
        Cocoa::Graphics::MaterialManager materialManager;
        Cocoa::Graphics::ShaderManager shaderManager(graphicsDevice);
        Cocoa::Graphics::RenderStatistics renderStats;
        Cocoa::Graphics::LineBatch sut(
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
        constexpr auto startPoint = Cocoa::Math::Vector2f(0.0, 0.0);
        constexpr auto endPoint = Cocoa::Math::Vector2f(0.0, 0.5);
        int materialHandleCounter{0};

        for (int i = 0; i < scenario.MaxSubmissionCount; ++i)
        {
            sut.Draw(
                materialHandles[materialHandleCounter],
                identity,
                color,
                startPoint,
                endPoint,
                0.5f,
                0.5f
            );

            if (materialHandleCounter < materialHandles.size() - 1)
            {
                materialHandleCounter++;
            }
        }

        sut.Flush(identity);

        EXPECT_EQ(scenario.ExpectedDrawCount, renderStats.DrawCount);
        EXPECT_EQ(scenario.ExpectedBatchFlushCount, renderStats.BatchFlushCount);
    }
}