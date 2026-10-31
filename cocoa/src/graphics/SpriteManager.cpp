#include "graphics/SpriteManager.hpp"

#include <stdexcept>

namespace cocoa::graphics
{
    SpriteManager::SpriteManager() :
        m_sprites(),
        m_handles(),
        m_nextId(1)
    {

    }

    SpriteManager::~SpriteManager() = default;

    SpriteHandle SpriteManager::load(
        const std::string& spriteId,
        const TextureHandle& textureHandle,
        const math::Vector2f& minPixel,
        const math::Vector2f& maxPixel,
        const math::Vector2f& textureSize)
    {
        if (const auto it = m_handles.find(spriteId); it != m_handles.end())
        {
            return it->second;
        }

        SpriteHandle handle {.id = m_nextId++ };
        Sprite sprite
        {
            .id = spriteId,
            .textureHandle = textureHandle,
            .minUV = {minPixel.x / textureSize.x, minPixel.y / textureSize.y},
            .maxUV = {maxPixel.x / textureSize.x, maxPixel.y / textureSize.y}
        };

        m_sprites.emplace(handle.id, sprite);
        m_handles.emplace(spriteId, handle);

        return handle;
    }

    const Sprite& SpriteManager::get(const SpriteHandle& handle) const
    {
        const auto it = m_sprites.find(handle.id);
        if (it == m_sprites.end())
        {
            throw std::runtime_error(
                "No Sprite found with the sprite id: " +
                std::to_string(handle.id)
            );
        }

        return it->second;
    }
}
