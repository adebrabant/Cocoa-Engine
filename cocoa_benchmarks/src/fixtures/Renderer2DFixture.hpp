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

namespace CocoaBenchmarks
{
    class Renderer2DFixture : public benchmark::Fixture
    {
    public:
        void SetUp(const benchmark::State&) override
        {
            m_shader = m_shaderManager.Load("benchmark_shader", "", "");

            const cocoa::Graphics::TextureSpec spec{
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
                "benchmark_material", m_shader, "alpha", cocoa::Core::Color{}
            );
            m_sprite = m_spriteManager.Load(
                "benchmark_sprite", m_texture,
                cocoa::Math::Vector2f{0.0f, 0.0f},
                cocoa::Math::Vector2f{2.0f, 2.0f},
                cocoa::Math::Vector2f{2.0f, 2.0f}
            );
        }

    protected:
        StubGraphicsDevice m_device;
        cocoa::Graphics::ShaderManager m_shaderManager{m_device};
        cocoa::Graphics::TextureManager m_textureManager{m_device};
        cocoa::Graphics::MaterialManager m_materialManager;
        cocoa::Graphics::SpriteManager m_spriteManager;
        cocoa::Graphics::Renderer2D m_renderer{
            m_device, m_shaderManager, m_textureManager,
            m_materialManager, m_spriteManager
        };

        cocoa::Graphics::ShaderHandle m_shader{};
        cocoa::Graphics::TextureHandle m_texture{};
        cocoa::Graphics::MaterialHandle m_material{};
        cocoa::Graphics::SpriteHandle m_sprite{};
    };
}
