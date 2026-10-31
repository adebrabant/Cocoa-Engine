#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "graphics/Sprite.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace cocoa::graphics
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
            const math::Vector2f& minPixel,
            const math::Vector2f& maxPixel,
            const math::Vector2f& textureSize
        );
        const Sprite& Get(const SpriteHandle& handle) const;

    private:
        std::unordered_map<uint32_t, Sprite> m_sprites;
        std::unordered_map<std::string, SpriteHandle> m_handles;
        uint32_t m_nextId;
    };
}
