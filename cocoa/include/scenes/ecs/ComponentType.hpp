#pragma once

#include <cstdint>

namespace cocoa::scenes
{
    inline uint32_t getNextComponentTypeId() {
        static uint32_t nextId = 0;
        return nextId++;
    }

    template<typename T>
    struct ComponentType
    {
        static uint32_t getId()
        {
            static uint32_t id = getNextComponentTypeId();
            return id;
        }
    };
}
