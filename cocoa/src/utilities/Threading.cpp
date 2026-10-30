#include "utilities/Threading.hpp"

namespace cocoa
{
    void SafeJoin(std::thread& thread)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}
