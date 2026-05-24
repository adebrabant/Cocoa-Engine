#include "Graphics/Renderer2D.hpp"

namespace VexEngine::Graphics
{
	Renderer2D::Renderer2D(IGraphicsDevice& graphicsDevice) :
		m_graphicsDevice(graphicsDevice)
	{

	}

	void Renderer2D::BeginScene()
	{
		//ToDo: Store camera/view-projection data
		//ToDo: Reset batch/queue state
	}

	void Renderer2D::EndScene()
	{
		// ToDo: Flush queued 2D draw commands
	}
}