#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

class EventManager;
class EntityManager;

class BaseSystem
{
public:
    virtual void update(EntityManager& entities, EventManager& events, float dt) = 0;
    virtual void render(EntityManager& entities){};
    virtual void wake(EventManager& events);

protected:
    static uint32_t counter;
};


template <typename MainClass>
class System : public BaseSystem
{
    
private:
    static uint32_t getID()
    {
        static uint32_t id = counter++;
        return id;
    }

    friend class SystemManager;
};


class SystemManager
{
public:
    SystemManager(EntityManager& entities, EventManager& events);
    void updateSystems(float dt);
    void lateUpdateSystems();

    void wake();

    template <typename S, typename ... Args>
    void add(Args && ... args)
    {
        std::shared_ptr<S> s(new S(std::forward<Args>(args) ...));
        systems.insert(std::make_pair(S::getID(), s));
    }

private:
    EntityManager& entities;
    EventManager& events;
    std::unordered_map<uint32_t, std::shared_ptr<BaseSystem>> systems;
};

