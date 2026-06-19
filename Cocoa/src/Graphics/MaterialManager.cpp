#include "Graphics/MaterialManager.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/Material.hpp"
#include "Core/Color.hpp"

#include <string>
#include <utility>
#include <stdexcept>

namespace Cocoa::Graphics
{
	MaterialManager::MaterialManager() :
		m_handles(),
		m_materials(),
		m_nextId(1)
	{

	}

	MaterialManager::~MaterialManager() = default;

	MaterialHandle MaterialManager::Load(
		const std::string& materialId, 
		ShaderHandle shaderHandle, 
		TextureHandle textureHandle, 
		Core::Color tint)
	{
		if (auto it = m_handles.find(materialId); it != m_handles.end())
		{
			return it->second;
		}

		MaterialHandle handle{ .Id = m_nextId++ };
		Material material
		{
			.Id = materialId,
			.ShaderHandle = shaderHandle,
			.TextureHandle = textureHandle
		};
		
		m_handles.emplace(materialId, handle);
		m_materials.emplace(handle.Id, std::move(material));

		return handle;
	}

	const Material& MaterialManager::Get(MaterialHandle handle) const
	{
		auto it = m_materials.find(handle.Id);

		if (it == m_materials.end())
		{
			throw std::runtime_error(
				"No Material found with the material id: " +
				std::to_string(handle.Id)
			);
		}

		return it->second;
	}
}