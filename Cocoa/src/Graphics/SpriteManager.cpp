#include "Graphics/SpriteManager.hpp"

#include <stdexcept>

namespace Cocoa::Graphics
{
    SpriteManager::SpriteManager() :
        m_sprites(),
        m_handles(),
        m_nextId(1)
    {

    }

    SpriteManager::~SpriteManager() = default;

    SpriteHandle SpriteManager::Load(
        const std::string& spriteId,
        const TextureHandle& textureHandle,
        const Math::Vector2f& minUV,
        const Math::Vector2f& maxUV)
    {
        if (const auto it = m_handles.find(spriteId); it != m_handles.end())
        {
            return it->second;
        }

        SpriteHandle handle {.Id = m_nextId++ };
        Sprite sprite
        {
            .Id = spriteId,
            .Texture = textureHandle,
            .MinUV = minUV,
            .MaxUV = maxUV
        };

        m_sprites.emplace(handle.Id, sprite);
        m_handles.emplace(spriteId, handle);

        return handle;
    }

    const Sprite& SpriteManager::Get(const SpriteHandle& handle)
    {
        const auto it = m_sprites.find(handle.Id);
        if (it == m_sprites.end())
        {
            throw std::runtime_error(
                "No Sprite found with the sprite id: " +
                std::to_string(handle.Id)
            );
        }

        return it->second;
    }
}
