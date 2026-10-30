#pragma once

#include <vector>

namespace cocoa::Assets
{
	struct Image
	{
		std::vector<uint8_t> Pixels;
		int Width{ 0 };
		int Height{ 0 };
		int Channels{ 4 };
	};
}