#include "graphics/ShaderManager.hpp"
#include "graphics/GraphicsDevice.hpp"
#include "graphics/Shader.hpp"

#include <stdexcept>
#include <utility>

namespace cocoa::graphics
{
	ShaderManager::ShaderManager(GraphicsDevice& graphicsDevice) :
		m_graphicsDevice(graphicsDevice),
		m_handles(),
		m_shaders(),
		m_nextId(1)
	{

	}

	ShaderManager::~ShaderManager() = default;

	ShaderHandle ShaderManager::load(
		const std::string& shaderId,
		const std::string& vertexSource,
		const std::string& fragmentSource)
	{
		if (auto it = m_handles.find(shaderId); it != m_handles.end())
		{
			return it->second;
		}

		ShaderHandle handle{ .id = m_nextId++ };
		Unique<Shader> shader = m_graphicsDevice.createShader(
			vertexSource,
			fragmentSource
		);

		m_handles.emplace(shaderId, handle);
		m_shaders.emplace(handle.id, std::move(shader));

		return handle;
	}

	const Shader& ShaderManager::get(ShaderHandle handle) const
	{
		auto it = m_shaders.find(handle.id);

		if (it == m_shaders.end())
		{
			throw std::runtime_error(
				"No Shader found with the shader handle id: " +
				std::to_string(handle.id)
			);
		}

		return *it->second;
	}

	const bool ShaderManager::tryGetHandle(const std::string& id, ShaderHandle& outHandle) const
	{
		if (auto it = m_handles.find(id); it != m_handles.end())
		{
			outHandle = it->second;
			return true;
		}

		outHandle = ShaderHandle{ .id = 0 };
		return false;
	}
}
