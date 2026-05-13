#include "Assets/AssetPathProvider.hpp"

#include <iostream>
#include <vector>

namespace VexEngine::Assets
{
    std::filesystem::path AssetPathProvider::GetAssetsPath() const
    {
        try
        {
            auto exePath = std::filesystem::canonical(std::filesystem::current_path());

            std::vector<std::filesystem::path> candidates =
            {
                exePath / m_assetPathName,
                exePath.parent_path() / m_assetPathName,
                exePath / "Debug" / m_assetPathName,
                exePath / "Release" / m_assetPathName
            };

            for (auto& path : candidates)
            {
                if (std::filesystem::exists(path))
                    return path;
            }

            std::cerr << "Warning: Assets folder not found! Using default textures." << std::endl;
            return {};
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            std::cerr << "Error locating Assets folder: " << e.what() << std::endl;
            return {};
        }
    }
}