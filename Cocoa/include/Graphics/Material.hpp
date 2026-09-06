#pragma once

#include "Graphics/GraphicsHandles.hpp"
#include "Core/Color.hpp"
#include <string>

namespace Cocoa::Graphics
{
	struct Material
	{
		std::string Id;
		ShaderHandle Shader;
		Core::Color Tint;
	};
}