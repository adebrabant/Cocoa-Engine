#include "fixtures/Renderer2DFixture.hpp"

#include <benchmark/benchmark.h>
#include <random>
#include <vector>

namespace CocoaBenchmarks
{
    BENCHMARK_DEFINE_F(Renderer2DFixture, EndDraw_SingleSortingLayer)(benchmark::State& state)
    {
        std::mt19937 generator{ 42 };
        std::uniform_int_distribution<int> distribution{0, 5};

        std::vector<int> sortingOrders;
        sortingOrders.reserve(state.range(0));

        for (auto i = 0; i < state.range(0); ++i)
        {
            sortingOrders.push_back(distribution(generator));
        }

        for (auto _ : state)
        {
            state.PauseTiming();
            m_renderer.BeginDraw(cocoa::Math::Matrix4f{});
            state.ResumeTiming();

            for (auto i = 0; i < state.range(0); ++i)
            {
                m_renderer.DrawQuad(
                    cocoa::Math::Matrix4f {},
                    m_material,
                    m_texture,
                    cocoa::Math::Vector2f {},
                    cocoa::Graphics::SortLayer::Background,
                    sortingOrders[i]
                );
            }

            m_renderer.EndDraw();
        }
    }

    BENCHMARK_REGISTER_F(Renderer2DFixture, EndDraw_SingleSortingLayer)
        ->Arg(1000)
        ->Arg(10000)
        ->Arg(50000)
        ->Arg(100000);

    BENCHMARK_DEFINE_F(Renderer2DFixture, EndDraw_MultiSortingLayer)(benchmark::State& state)
    {
        std::mt19937 generator{ 42 };
        std::uniform_int_distribution<int> distribution{0, 5};

        std::vector<int> sortingOrders;
        sortingOrders.reserve(state.range(0));

        constexpr std::array layers{
            cocoa::Graphics::SortLayer::Background,
            cocoa::Graphics::SortLayer::World,
            cocoa::Graphics::SortLayer::Foreground,
            cocoa::Graphics::SortLayer::UI
        };

        std::uniform_int_distribution<size_t> layerDistribution{
            0, layers.size() - 1
        };

        std::vector<cocoa::Graphics::SortLayer> randomLayers;
        randomLayers.reserve(state.range(0));

        for (auto i = 0; i < state.range(0); ++i)
        {
            sortingOrders.push_back(distribution(generator));
            randomLayers.emplace_back(layers[layerDistribution(generator)]);
        }

        for (auto _ : state)
        {
            state.PauseTiming();
            m_renderer.BeginDraw(cocoa::Math::Matrix4f{});
            state.ResumeTiming();

            for (auto i = 0; i < state.range(0); ++i)
            {
                m_renderer.DrawQuad(
                    cocoa::Math::Matrix4f {},
                    m_material,
                    m_texture,
                    cocoa::Math::Vector2f {},
                    randomLayers[i],
                    sortingOrders[i]
                );
            }

            m_renderer.EndDraw();
        }
    }

    BENCHMARK_REGISTER_F(Renderer2DFixture, EndDraw_MultiSortingLayer)
        ->Arg(1000)
        ->Arg(10000)
        ->Arg(50000)
        ->Arg(100000);
}