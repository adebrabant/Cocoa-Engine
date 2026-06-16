#pragma once

#include "Core/Memory.hpp"

#include <string>
#include <cstdint>
#include <unordered_map>

namespace Cocoa::Graphics
{
	class GraphicsDevice;
	class Shader;

	struct ShaderHandle
	{
		uint32_t Id;
	};

	class ShaderManager
	{
	public:
		ShaderManager(GraphicsDevice& graphicsDevice);
		~ShaderManager();

		ShaderManager(const ShaderManager&) = delete;
		ShaderManager& operator=(const ShaderManager&) = delete;

		ShaderHandle Load(
			const std::string& shaderId, 
			const std::string& vertexSource, 
			const std::string& fragmentSource
		);
		const Shader& Get(ShaderHandle handle) const;

	private:
		GraphicsDevice& m_graphicsDevice;
		std::unordered_map<std::string, ShaderHandle> m_handles;
		std::unordered_map<uint32_t, Unique<Shader>> m_shaders;
		uint32_t m_nextId;
	};
}