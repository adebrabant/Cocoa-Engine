#include "Graphics/ShaderManager.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/Shader.hpp"
#include "Core/Memory.hpp"

#include <string>
#include <utility>
#include <stdexcept>

namespace Cocoa::Graphics
{
	ShaderManager::ShaderManager(GraphicsDevice& graphicsDevice) :
		m_graphicsDevice(graphicsDevice),
		m_handles(),
		m_shaders(),
		m_nextId(1)
	{

	}

	ShaderManager::~ShaderManager() = default;

	ShaderHandle ShaderManager::Load(
		const std::string& shaderId, 
		const std::string& vertexSource, 
		const std::string& fragmentSource)
	{
		if (auto it = m_handles.find(shaderId); it != m_handles.end())
		{
			return it->second;
		}

		ShaderHandle handle{ .Id = m_nextId++ };
		Unique<Shader> shader = m_graphicsDevice.CreateShader(
			vertexSource,
			fragmentSource
		);

		m_handles.emplace(shaderId, handle);
		m_shaders.emplace(handle.Id, std::move(shader));

		return handle;
	}

	const Shader& ShaderManager::Get(ShaderHandle handle) const
	{
		auto it = m_shaders.find(handle.Id);

		if (it == m_shaders.end())
		{
			throw std::runtime_error(
				"No Shader found with the shader handle id: " +
				std::to_string(handle.Id)
			);
		}

		return *it->second;
	}
}