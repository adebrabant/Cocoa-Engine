#pragma once

#include <cstdint>

namespace Cocoa::Scenes
{
    inline uint32_t GetNextComponentTypeId() {
        static uint32_t nextId = 0;
        return nextId++;
    }

    template<typename T>
    struct ComponentType
    {
        static uint32_t GetId()
        {
            static uint32_t id = GetNextComponentTypeId();
            return id;
        }
    };
}