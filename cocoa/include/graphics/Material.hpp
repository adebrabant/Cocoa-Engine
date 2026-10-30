#pragma once

#include "core/Color.hpp"
#include "graphics/BlendMode.hpp"
#include "graphics/GraphicsHandles.hpp"
#include <string>

namespace cocoa::Graphics
{
	struct Material
	{
		std::string Id;
		ShaderHandle Shader;
		Core::Color Tint;
		BlendMode Blend;
	};
}
