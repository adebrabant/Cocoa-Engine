#pragma once

#include "core/Color.hpp"
#include "graphics/BlendMode.hpp"
#include "graphics/GraphicsHandles.hpp"
#include <string>

namespace cocoa::graphics
{
	struct Material
	{
		std::string Id;
		ShaderHandle Shader;
		core::Color Tint;
		BlendMode Blend;
	};
}
