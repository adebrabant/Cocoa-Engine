#include "Graphics/TextureManager.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/TextureSpec.hpp"
#include "Graphics/Texture2D.hpp"
#include "Core/Memory.hpp"

#include <string>
#include <utility>
#include <stdexcept>

namespace Cocoa::Graphics
{
	TextureManager::TextureManager(GraphicsDevice& graphicsDevice) :
		m_graphicsDevice(graphicsDevice),
		m_handles(),
		m_textures(),
		m_nextId(1)
	{

	}

	TextureManager::~TextureManager() = default;

	TextureHandle TextureManager::Load(const TextureSpec& spec, const void* pixels)
	{
		if (auto it = m_handles.find(spec.Id); it != m_handles.end())
		{
			return it->second;
		}

		if (pixels == nullptr)
		{
			throw std::runtime_error("Texture pixels cannot be null.");
		}

		TextureHandle handle{ .Id = m_nextId++ };
		Unique<Texture2D> texture = m_graphicsDevice.CreateTexture2D(
			spec,
			static_cast<const unsigned char*>(pixels)
		);

		m_handles.emplace(spec.Id, handle);
		m_textures.emplace(handle.Id, std::move(texture));

		return handle;
	}

	const Texture2D& TextureManager::Get(TextureHandle handle) const
	{
		auto it = m_textures.find(handle.Id);

		if (it == m_textures.end())
		{
			throw std::runtime_error(
				"No Texture found with the texture handle id: " +
				std::to_string(handle.Id)
			);
		}

		return *it->second;
	}
}