#include "utilities/Threading.hpp"

namespace cocoa
{
    void safeJoin(std::thread& thread)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}
