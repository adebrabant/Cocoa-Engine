#pragma once

#include <functional>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstddef>
#include <typeindex>
#include <unordered_map>
#include <any>

namespace Cocoa::Events
{
    class EventBus
    {
    public:
        template<typename Event>
        using HandlerFunc = std::function<void(const Event&)>;
        using SubscriptionToken = size_t;

        template<typename Event>
        SubscriptionToken Subscribe(HandlerFunc<Event> handler)
        {
            auto& handlers = GetHandlers<Event>();
            SubscriptionToken token = ++m_lastToken;
            handlers.emplace_back(token, std::move(handler));

            return token;
        }

        template<typename Event>
        void Unsubscribe(SubscriptionToken token)
        {
            auto& handlers = GetHandlers<Event>();
            handlers.erase(
                std::remove_if(handlers.begin(), handlers.end(),
                    [token](const auto& handlerPair)
                    {
                        return handlerPair.first == token;
                    }),
                handlers.end());
        }

        template<typename Event>
        bool HasSubscriber(SubscriptionToken token) const
        {
            const auto& handlers = GetHandlers<Event>();
            return std::any_of(handlers.begin(), handlers.end(),
                [token](const auto& handlerPair)
                {
                    return handlerPair.first == token;
                });
        }

        template<typename Event>
        void Publish(const Event& event) const
        {
            const auto& handlers = GetHandlers<Event>();
            for (const auto& [token, handler] : handlers)
            {
                handler(event);
            }
        }

    private:
        template<typename Event>
        using HandlerList = std::vector<std::pair<SubscriptionToken, HandlerFunc<Event>>>;

        template<typename Event>
        HandlerList<Event>& GetHandlers() const
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