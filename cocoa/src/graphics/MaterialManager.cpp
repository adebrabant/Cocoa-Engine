#include "graphics/MaterialManager.hpp"
#include "core/Color.hpp"
#include "graphics/Material.hpp"
#include "graphics/ShaderManager.hpp"

#include <algorithm>
#include <cctype>
#include <ranges>
#include <stdexcept>
#include <string>
#include <utility>

namespace cocoa::graphics
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

		// TODO: Add Warning Logs for default value used

		return BlendMode::Opaque;
	}

	MaterialManager::MaterialManager() :
		m_handles(),
		m_materials(),
		m_nextId(1)
	{

	}

	MaterialManager::~MaterialManager() = default;

	MaterialHandle MaterialManager::load(
		const std::string& materialId,
		const ShaderHandle shaderHandle,
		const std::string& blendMode,
		const core::Color tint)
	{
		if (const auto it = m_handles.find(materialId); it != m_handles.end())
		{
			return it->second;
		}

		MaterialHandle handle{ .id = m_nextId++ };
		Material material
		{
			.id = materialId,
			.shaderHandle = shaderHandle,
			.tint = tint,
			.blendMode =  ToBlendMode(blendMode)
		};

		m_handles.emplace(materialId, handle);
		m_materials.emplace(handle.id, std::move(material));

		return handle;
	}

	const Material& MaterialManager::get(const MaterialHandle handle) const
	{
		const auto it = m_materials.find(handle.id);

		if (it == m_materials.end())
		{
			throw std::runtime_error(
				"No Material found with the material id: " +
				std::to_string(handle.id)
			);
		}

		return it->second;
	}
}
