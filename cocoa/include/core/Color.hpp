#pragma once

namespace cocoa::core
{
	struct Color
	{
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;

		[[nodiscard]] constexpr bool operator==(const Color& other) const
		{
			if (r == other.r && g == other.g && b == other.b && a == other.a)
				return true;

			return false;
		}
	};
}
