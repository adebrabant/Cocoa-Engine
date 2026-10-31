#pragma once

#include "core/Color.hpp"
#include "graphics/BlendMode.hpp"
#include "graphics/GraphicsHandles.hpp"
#include <string>

namespace cocoa::graphics
{
	struct Material
	{
		std::string id;
		ShaderHandle shaderHandle;
		core::Color tint;
		BlendMode blendMode;
	};
}
