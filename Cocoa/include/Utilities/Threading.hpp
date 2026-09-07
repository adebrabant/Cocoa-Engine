#pragma once

#include <thread>
#include <utility>
#include <exception>

namespace Cocoa
{
    template<typename TWork>
    std::thread StartThread(TWork&& work, std::exception_ptr& error)
    {
        return std::thread{
            [work = std::forward<TWork>(work), &error]()
            {
                try
                {
                    work();
                }
                catch (...)
                {
                    error = std::current_exception();
                }
            }
        };
    }

    void SafeJoin(std::thread& thread);
}
