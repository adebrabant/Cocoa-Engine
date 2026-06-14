#include "Graphics/TextureSpec.hpp"

#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace Cocoa::Graphics
{
    namespace
    {
        std::string Normalize(std::string_view value)
        {
            std::string result;
            result.reserve(value.size());

            for (unsigned char c : value)
            {
                if (std::isspace(c) || c == '_' || c == '-')
                    continue;

                result.push_back(static_cast<char>(std::tolower(c)));
            }

            return result;
        }
    }

	TextureFormat TextureSpec::ParseFormat(std::string_view value, uint32_t channels)
	{
        const std::string normalized = Normalize(value);

        if (normalized == "auto")
            return channels == 4 ? TextureFormat::RGBA8 : TextureFormat::RGB8;

        if (normalized == "rgb8")
            return TextureFormat::RGB8;

        if (normalized == "rgba8")
            return TextureFormat::RGBA8;

        throw std::runtime_error("Invalid Texture format: " + std::string(value));
	}

	TextureFilter TextureSpec::ParseFilter(std::string_view value)
	{
        const std::string normalized = Normalize(value);

        if (normalized == "nearest")
            return TextureFilter::Nearest;

        if (normalized == "linear")
            return TextureFilter::Linear;

        if (normalized == "nearestmipmapnearest")
            return TextureFilter::NearestMipmapNearest;

        if (normalized == "linearmipmapnearest")
            return TextureFilter::LinearMipmapNearest;

        if (normalized == "nearestmipmaplinear")
            return TextureFilter::NearestMipmapLinear;

        if (normalized == "linearmipmaplinear")
            return TextureFilter::LinearMipmapLinear;

        throw std::runtime_error("Invalid texture filter: " + std::string(value));
	}

	TextureWrap TextureSpec::ParseWrap(std::string_view value)
	{
        const std::string normalized = Normalize(value);

        if (normalized == "repeat")
            return TextureWrap::Repeat;

        if (normalized == "clamptoedge")
            return TextureWrap::ClampToEdge;

        throw std::runtime_error("Invalid texture wrap: " + std::string(value));
	}
}