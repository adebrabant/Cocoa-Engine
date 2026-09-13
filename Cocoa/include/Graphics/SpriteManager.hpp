#pragma once

#include "Graphics/Sprite.hpp"
#include "Graphics/GraphicsHandles.hpp"

#include <string>
#include <cstdint>
#include <unordered_map>

namespace Cocoa::Graphics
{
    class SpriteManager
    {
    public:
        SpriteManager();
        ~SpriteManager();

        SpriteManager(const SpriteManager&) = delete;
        SpriteManager& operator=(const SpriteManager&) = delete;

        SpriteHandle Load(
            const std::string& spriteId,
            const TextureHandle& textureHandle,
            const Math::Vector2f& minPixel,
            const Math::Vector2f& maxPixel,
            const Math::Vector2f& textureSize
        );
        const Sprite& Get(const SpriteHandle& handle) const;

    private:
        std::unordered_map<uint32_t, Sprite> m_sprites;
        std::unordered_map<std::string, SpriteHandle> m_handles;
        uint32_t m_nextId;
    };
}