#pragma once

#include "math/Vector3f.hpp"

namespace cocoa::scenes
{
	struct TransformComponent
	{
		math::Vector3f Position{0.0f, 0.0f, 0.0f };
		math::Vector3f Rotation{ 0.0f, 0.0f, 0.0f };
		math::Vector3f Scale{1.0f, 1.0f, 1.0f };
	};
}
