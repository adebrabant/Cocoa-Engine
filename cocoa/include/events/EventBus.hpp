#pragma once

#include <functional>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstddef>
#include <typeindex>
#include <unordered_map>
#include <any>

namespace cocoa::events
{
    class EventBus
    {
    public:
        template<typename Event>
        using HandlerFunc = std::function<void(const Event&)>;
        using SubscriptionToken = size_t;

        template<typename Event>
        SubscriptionToken subscribe(HandlerFunc<Event> handler)
        {
            auto& handlers = getHandlers<Event>();
            SubscriptionToken token = ++m_lastToken;
            handlers.emplace_back(token, std::move(handler));

            return token;
        }

        template<typename Event>
        void unsubscribe(SubscriptionToken token)
        {
            auto& handlers = getHandlers<Event>();
            handlers.erase(
                std::remove_if(handlers.begin(), handlers.end(),
                    [token](const auto& handlerPair)
                    {
                        return handlerPair.first == token;
                    }),
                handlers.end());
        }

        template<typename Event>
        bool hasSubscriber(SubscriptionToken token) const
        {
            const auto& handlers = getHandlers<Event>();
            return std::any_of(handlers.begin(), handlers.end(),
                [token](const auto& handlerPair)
                {
                    return handlerPair.first == token;
                });
        }

        template<typename Event>
        void publish(const Event& event) const
        {
            const auto& handlers = getHandlers<Event>();
            for (const auto& [token, handler] : handlers)
            {
                handler(event);
            }
        }

    private:
        template<typename Event>
        using HandlerList = std::vector<std::pair<SubscriptionToken, HandlerFunc<Event>>>;

        template<typename Event>
        HandlerList<Event>& getHandlers() const
        {
            auto& anyRef = m_handlerMap[typeid(Event)];
            if (!anyRef.has_value())
            {
                anyRef = HandlerList<Event>{};
            }
            return std::any_cast<HandlerList<Event>&>(anyRef);
        }

    private:
        mutable std::unordered_map<std::type_index, std::any> m_handlerMap;
        SubscriptionToken m_lastToken = 0;
    };
}
