#pragma once

namespace Cocoa::Core
{
	struct Color
	{
		float R = 1.0f;
		float G = 1.0f;
		float B = 1.0f;
		float A = 1.0f;

		[[nodiscard]] constexpr bool operator==(const Color& other) const
		{
			if (R == other.R && G == other.G && B == other.B && A == other.A)
				return true;

			return false;
		}
	};
}