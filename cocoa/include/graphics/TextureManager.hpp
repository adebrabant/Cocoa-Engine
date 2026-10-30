#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "utilities/Memory.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace cocoa::Graphics
{
	class GraphicsDevice;
	class Texture2D;
	struct TextureSpec;

	class TextureManager
	{
	public:
		explicit TextureManager(GraphicsDevice& graphicsDevice);
		~TextureManager();

		TextureManager(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;

		TextureHandle Load(const TextureSpec& spec, const void* pixels);
		const Texture2D& Get(TextureHandle handle) const;
		bool TryGetHandle(const std::string& id, TextureHandle& outHandle) const;

	private:
		GraphicsDevice& m_graphicsDevice;
		std::unordered_map<std::string, TextureHandle> m_handles;
		std::unordered_map<uint32_t, Unique<Texture2D>> m_textures;
		uint32_t m_nextId;
	};
}