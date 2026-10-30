#include "assets/AssetPathProvider.hpp"

#include <array>
#include <iostream>

namespace cocoa::Assets
{
    AssetPathProvider::AssetPathProvider()
    {
        m_assetPath = FindPath("resources");

        if (!m_assetPath.empty())
            m_metadataPath = m_assetPath / "metadata";
    }

    std::filesystem::path AssetPathProvider::FindPath(const std::string& path)
    {
        try
        {
            auto exePath = std::filesystem::canonical(std::filesystem::current_path());

            std::array<std::filesystem::path, 4> candidates =
            {
                exePath / path,
                exePath.parent_path() / path,
                exePath / "Debug" / path,
                exePath / "Release" / path
            };

            for (auto& path : candidates)
            {
                if (std::filesystem::exists(path))
                    return path;
            }

            std::cerr << "Warning: Resources folder not found! Using default values." << std::endl;
            return {};
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            std::cerr << "Error locating Resources folder: " << e.what() << std::endl;
            return {};
        }
    }
}