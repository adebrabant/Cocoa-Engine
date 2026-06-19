#pragma once

#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"

#include <string>

namespace Cocoa::Graphics
{
	struct Material
	{
		std::string Id;
		ShaderHandle ShaderHandle;
		TextureHandle TextureHandle;
	};
}