#pragma once

#include "Graphics/IGraphicsDevice.hpp"
#include <cstdint>

namespace VexEngine::Graphics
{
	class OpenGLGraphicsDevice : public IGraphicsDevice
	{
	public:
		OpenGLGraphicsDevice() = default;
		~OpenGLGraphicsDevice() = default;
		void SetViewport(uint32_t width, uint32_t height) override;
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void Clear() override;
	};
}