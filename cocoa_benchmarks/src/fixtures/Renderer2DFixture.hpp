#pragma once

#include "stubs/graphics/StubGraphicsDevice.hpp"
#include <core/Color.hpp>
#include <graphics/MaterialManager.hpp>
#include <graphics/Renderer2D.hpp>
#include <graphics/ShaderManager.hpp>
#include <graphics/SpriteManager.hpp>
#include <graphics/TextureManager.hpp>
#include <graphics/TextureSpec.hpp>
#include <math/Matrix4f.hpp>
#include <math/Vector2f.hpp>

#include <array>
#include <benchmark/benchmark.h>

namespace cocoa_benchmarks
{
    class Renderer2DFixture : public benchmark::Fixture
    {
    public:
        void SetUp(const benchmark::State&) override
        {
            m_shader = m_shaderManager.Load("benchmark_shader", "", "");

            const cocoa::graphics::TextureSpec spec{
                .Id = "benchmark_texture",
                .Width = 2,
                .Height = 2
            };
            constexpr std::array<unsigned char, 16> pixels{
                255, 255, 255, 255, 255, 255, 255, 255,
                255, 255, 255, 255, 255, 255, 255, 255
            };
            m_texture = m_textureManager.Load(spec, pixels.data());
            m_material = m_materialManager.Load(
                "benchmark_material", m_shader, "alpha", cocoa::core::Color{}
            );
            m_sprite = m_spriteManager.Load(
                "benchmark_sprite", m_texture,
                cocoa::math::Vector2f{0.0f, 0.0f},
                cocoa::math::Vector2f{2.0f, 2.0f},
                cocoa::math::Vector2f{2.0f, 2.0f}
            );
        }

    protected:
        StubGraphicsDevice m_device;
        cocoa::graphics::ShaderManager m_shaderManager{m_device};
        cocoa::graphics::TextureManager m_textureManager{m_device};
        cocoa::graphics::MaterialManager m_materialManager;
        cocoa::graphics::SpriteManager m_spriteManager;
        cocoa::graphics::Renderer2D m_renderer{
            m_device, m_shaderManager, m_textureManager,
            m_materialManager, m_spriteManager
        };

        cocoa::graphics::ShaderHandle m_shader{};
        cocoa::graphics::TextureHandle m_texture{};
        cocoa::graphics::MaterialHandle m_material{};
        cocoa::graphics::SpriteHandle m_sprite{};
    };
}
