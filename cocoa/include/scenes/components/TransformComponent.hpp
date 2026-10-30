#pragma once

#include "math/Vector3f.hpp"

namespace cocoa::Scenes
{
	struct TransformComponent
	{
		Math::Vector3f Position{0.0f, 0.0f, 0.0f };
		Math::Vector3f Rotation{ 0.0f, 0.0f, 0.0f };
		Math::Vector3f Scale{1.0f, 1.0f, 1.0f };
	};
}