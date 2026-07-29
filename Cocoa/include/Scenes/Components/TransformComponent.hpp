#pragma once

#include "Math/Vector3f.hpp"

namespace Cocoa::Scenes
{
	struct TransformComponent
	{
		Math::Vector3f Position;
		Math::Vector3f Rotation;
		Math::Vector3f Scale;
	};
}