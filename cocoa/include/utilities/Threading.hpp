#pragma once

#include <thread>
#include <utility>
#include <exception>

namespace cocoa
{
    template<typename TWork>
    std::thread startThread(TWork&& work, std::exception_ptr& error)
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

    void safeJoin(std::thread& thread);
}
