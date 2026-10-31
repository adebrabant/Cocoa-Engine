#pragma once

#include "graphics/GraphicsHandles.hpp"
#include "utilities/Memory.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace cocoa::graphics
{
	class GraphicsDevice;
	class Shader;

	class ShaderManager
	{
	public:
		explicit ShaderManager(GraphicsDevice& graphicsDevice);
		~ShaderManager();

		ShaderManager(const ShaderManager&) = delete;
		ShaderManager& operator=(const ShaderManager&) = delete;

		ShaderHandle load(
			const std::string& shaderId,
			const std::string& vertexSource,
			const std::string& fragmentSource
		);
		const Shader& get(ShaderHandle handle) const;
		const bool tryGetHandle(const std::string& id, ShaderHandle& outHandle) const;

	private:
		GraphicsDevice& m_graphicsDevice;
		std::unordered_map<std::string, ShaderHandle> m_handles;
		std::unordered_map<uint32_t, Unique<Shader>> m_shaders;
		uint32_t m_nextId;
	};
}
