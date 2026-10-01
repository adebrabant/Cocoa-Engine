#include "Graphics/MaterialManager.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/Material.hpp"
#include "Core/Color.hpp"

#include <string>
#include <utility>
#include <stdexcept>
#include <ranges>
#include <algorithm>
#include <cctype>

namespace Cocoa::Graphics
{
	static BlendMode ToBlendMode(const std::string& blendMode)
	{
		auto scrubbedView = blendMode
			| std::views::filter([](const unsigned char c) { return !std::isspace(c);})
			| std::views::transform([](const unsigned char c){ return std::tolower(c);});

		const std::string cleanedBlendMode(scrubbedView.begin(), scrubbedView.end());

		if (cleanedBlendMode == "opaque")
			return BlendMode::Opaque;

		if (cleanedBlendMode == "alpha")
			return BlendMode::Alpha;

		if (cleanedBlendMode == "additive")
			return BlendMode::Additive;

		if (cleanedBlendMode == "subtractive")
			return BlendMode::Subtractive;

		if (cleanedBlendMode == "reversesubtract")
			return BlendMode::ReverseSubtract;

		return BlendMode::Opaque;
	}

	MaterialManager::MaterialManager() :
		m_handles(),
		m_materials(),
		m_nextId(1)
	{

	}

	MaterialManager::~MaterialManager() = default;

	MaterialHandle MaterialManager::Load(
		const std::string& materialId, 
		const ShaderHandle shaderHandle,
		const std::string& blendMode,
		const Core::Color tint)
	{
		if (const auto it = m_handles.find(materialId); it != m_handles.end())
		{
			return it->second;
		}

		MaterialHandle handle{ .Id = m_nextId++ };
		Material material
		{
			.Id = materialId,
			.Shader = shaderHandle,
			.Tint = tint,
			.Blend =  ToBlendMode(blendMode)
		};
		
		m_handles.emplace(materialId, handle);
		m_materials.emplace(handle.Id, std::move(material));

		return handle;
	}

	const Material& MaterialManager::Get(const MaterialHandle handle) const
	{
		const auto it = m_materials.find(handle.Id);

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