#include "Utilities/Threading.hpp"

namespace Cocoa
{
    void SafeJoin(std::thread& thread)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}
