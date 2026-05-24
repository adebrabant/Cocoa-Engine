#pragma once

#include "Graphics/IGraphicsDevice.hpp"

namespace VexEngine::Graphics
{
	class Renderer2D
	{
	public:
		Renderer2D(IGraphicsDevice& graphicsDevice);
		~Renderer2D() = default;
		void BeginScene();
		void EndScene();

	private:
		IGraphicsDevice& m_graphicsDevice;
	};
}