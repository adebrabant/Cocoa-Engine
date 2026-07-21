#pragma once

#include "Graphics/Material.hpp"
#include "Graphics/GraphicsHandles.hpp"

#include <string>
#include <cstdint>
#include <unordered_map>

namespace Cocoa::Core
{
	struct Color;
}

namespace Cocoa::Graphics
{
	struct TextureHandle;
	struct ShaderHandle;

	class MaterialManager
	{
	public:
		MaterialManager();
		~MaterialManager();

		MaterialManager(const MaterialManager&) = delete;
		MaterialManager& operator=(const MaterialManager&) = delete;

		MaterialHandle Load(
			const std::string& materialId,
			ShaderHandle shaderHandle,
			TextureHandle textureHandle,
			Core::Color tint
		);

		const Material& Get(MaterialHandle handle) const;

	private:
		std::unordered_map<std::string, MaterialHandle> m_handles;
		std::unordered_map<uint32_t, Material> m_materials;
		uint32_t m_nextId;
	};
}