#pragma once

#include <cstdint>
#include <vector>

namespace cocoa::assets
{
	struct Image
	{
		std::vector<uint8_t> pixels;
		int width{ 0 };
		int height{ 0 };
		int channels{ 4 };
	};
}
