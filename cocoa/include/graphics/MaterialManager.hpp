#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "graphics/Material.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace cocoa::Core
{
	struct Color;
}

namespace cocoa::Graphics
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
			const std::string& blendMode,
			Core::Color tint
		);

		const Material& Get(MaterialHandle handle) const;

	private:
		std::unordered_map<std::string, MaterialHandle> m_handles;
		std::unordered_map<uint32_t, Material> m_materials;
		uint32_t m_nextId;
	};
}
