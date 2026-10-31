#pragma once

#include "math/Vector3f.hpp"

namespace cocoa::scenes
{
	struct TransformComponent
	{
		math::Vector3f position{0.0f, 0.0f, 0.0f };
		math::Vector3f rotation{ 0.0f, 0.0f, 0.0f };
		math::Vector3f scale{1.0f, 1.0f, 1.0f };
	};
}
