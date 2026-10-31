#pragma once

#include <memory>
#include <utility>

namespace cocoa
{
    template<typename T>
    using Unique = std::unique_ptr<T>;

    template<typename T, typename... Args>
    Unique<T> createUnique(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Shared = std::shared_ptr<T>;

    template<typename T, typename... Args>
    Shared<T> createShared(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Weak = std::weak_ptr<T>;
}
