#pragma once

#include "Graphics/GraphicsHandles.hpp"

#include <string>

namespace Cocoa::Graphics
{
	struct Material
	{
		std::string Id;
		ShaderHandle ShaderId;
		TextureHandle TextureId;
	};
}