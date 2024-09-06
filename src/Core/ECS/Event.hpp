#pragma once
#include <functional>
#include <map>
#include <vector>

class EventIDGenerator
{
public:
    template<typename T>
    static int getID()
    {
        static uint32_t id = counter++;
        return id;
    }
private:
    static uint32_t counter;
};

uint32_t EventIDGenerator::counter = 0u;


class EventManager
{
public:
    template<typename EventType, typename Receiver>
    void subscribe(Receiver* receiver)
    {
        void (Receiver::*receive)(const EventType&) = &Receiver::receive;

        auto callback = [receiver, receive](const void* event)
            {
            (receiver->*receive)(*static_cast<const EventType*>(event));
            };

        uint32_t eventID = EventIDGenerator::getID<EventType>();
        auto& subscribers = subscribers_[eventID];

        subscribers.push_back({ callback, receiver });
    }

    template<typename EventType, typename Receiver>
    void unsubscribe(Receiver* receiver) {
        uint32_t eventID = EventIDGenerator::getID<EventType>();
        auto& subscribers = subscribers_[eventID];

        subscribers.erase(
            std::remove_if(subscribers.begin(), subscribers.end(),
                [receiver](const Subscriber& sub)
                {
                    return sub.receiver == receiver;
                }),
            subscribers.end()
        );
    }

    template<typename EventType, typename... Args>
    void emit(Args&&... args)
    {
        uint32_t eventID = EventIDGenerator::getID<EventType>();
        EventType event(std::forward<Args>(args)...);
        auto& subscribers = subscribers_[eventID];
        for (auto& subscriber : subscribers)
        {
            subscriber.callback(&event);
        }
    }

private:
    struct Subscriber
    {
        std::function<void(const void*)> callback;
        void* receiver;
    };

    std::map<uint32_t, std::vector<Subscriber>> subscribers_;
};