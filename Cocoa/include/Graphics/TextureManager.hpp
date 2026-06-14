#pragma once

#include "Core/Memory.hpp"
#include "Graphics/Texture2D.hpp"

#include <cstdint>
#include <unordered_map>
#include <string>

namespace Cocoa::Graphics
{
	class GraphicsDevice;
	struct TextureSpec;

	struct TextureHandle
	{
		uint32_t id;
	};

	class TextureManager
	{
	public:
		TextureManager(GraphicsDevice& graphicsDevice);
		~TextureManager();

		TextureManager(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;

		TextureHandle Load(const TextureSpec& spec, const void* pixels);
		const Texture2D& Get(TextureHandle handle) const;

	private:
		GraphicsDevice& m_graphicsDevice;
		std::unordered_map<std::string, TextureHandle> m_handles;
		std::unordered_map<uint32_t, Unique<Texture2D>> m_textures;
		uint32_t m_nextId;
	};
}