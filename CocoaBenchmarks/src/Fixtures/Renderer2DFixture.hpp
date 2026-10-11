#pragma once

#include <Graphics/Renderer2D.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/TextureManager.hpp>
#include <Graphics/MaterialManager.hpp>
#include <Graphics/SpriteManager.hpp>
#include <Graphics/TextureSpec.hpp>
#include <Core/Color.hpp>
#include <Math/Matrix4f.hpp>
#include <Math/Vector2f.hpp>
#include "Stubs/Graphics/StubGraphicsDevice.hpp"

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

            const Cocoa::Graphics::TextureSpec spec{
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
                "benchmark_material", m_shader, "alpha", Cocoa::Core::Color{}
            );
            m_sprite = m_spriteManager.Load(
                "benchmark_sprite", m_texture,
                Cocoa::Math::Vector2f{0.0f, 0.0f},
                Cocoa::Math::Vector2f{2.0f, 2.0f},
                Cocoa::Math::Vector2f{2.0f, 2.0f}
            );
        }

    protected:
        StubGraphicsDevice m_device;
        Cocoa::Graphics::ShaderManager m_shaderManager{m_device};
        Cocoa::Graphics::TextureManager m_textureManager{m_device};
        Cocoa::Graphics::MaterialManager m_materialManager;
        Cocoa::Graphics::SpriteManager m_spriteManager;
        Cocoa::Graphics::Renderer2D m_renderer{
            m_device, m_shaderManager, m_textureManager,
            m_materialManager, m_spriteManager
        };

        Cocoa::Graphics::ShaderHandle m_shader{};
        Cocoa::Graphics::TextureHandle m_texture{};
        Cocoa::Graphics::MaterialHandle m_material{};
        Cocoa::Graphics::SpriteHandle m_sprite{};
    };
}
