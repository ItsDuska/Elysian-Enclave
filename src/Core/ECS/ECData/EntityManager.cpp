#include "EntityManager.hpp"
#include <cassert>


int util::componentCounter = 0;


ComponentPool::ComponentPool()
{
    data = nullptr;
    elementSize = 0;
}

ComponentPool::ComponentPool(size_t elementsize)
{
    assert(elementSize == 0);
    elementSize = elementsize;
    data = new char[elementSize * MAX_ENTITIES];
}

/*
ComponentPool::~ComponentPool()
{
    delete[] data;
}
*/

void ComponentPool::clean()
{
    delete[] data;
}

void* ComponentPool::get(size_t index)
{
    return data + index * elementSize;
}

bool ComponentPool::isNull()
{
    return (data == nullptr);
}


// ------------------------------------------------------------

EntityID EntityManager::newEnity()
{
    if (!freeEntities.empty())
    {

        EntityIndex newIndex = freeEntities.back();
        freeEntities.pop_back();
        EntityID newID = CreateEntityId(newIndex, GetEntityVersion(entities[newIndex].id));
        entities[newIndex].id = newID;

        return entities[newIndex].id;
    }

    entities.push_back({ CreateEntityId(EntityIndex(entities.size()), 0), ComponentMask() });
    return entities.back().id;
}

void EntityManager::removeEntity(EntityID id)
{
    const EntityIndex index = GetEntityIndex(id);

    EntityID newID = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
    entities[index].id = newID;
    entities[index].mask.reset();
    freeEntities.push_back(index);
}

EntityManager::~EntityManager()
{
    for (auto& pool : componentPools)
    {
        pool.clean();
    }
}


/*
template<typename Component>
Component* EntityManager::addComponent(EntityID id)
{
    const EntityIndex index = GetEntityIndex(id);
    const int componentID = util::generateNewID<Component>();

    if (componentPools.size() <= componentID)
    {
        componentPools.resize(componentID + 1);
    }

    if (componentPools[componentID] == nullptr)
    {
        componentPools[componentID] = new ComponentPool(sizeof(Component));
    }

    Component* component = new (componentPools[componentID]->get(index)) Component();
    entities[index].mask.set(componentID);
    return component;
}

*/


template<typename Component>
void EntityManager::removeComponent(EntityID id)
{
    const EntityIndex index = GetEntityIndex(id);

    if (entities[index].id != id)
    {
        return;
    }

    const int componentID = util::generateNewID<Component>();
    entities[index].mask.reset(componentID);
}

unsigned long long enA;

EntityID CreateEntityId(EntityIndex index, EntityVersion version)
{
    return ((EntityID)index << 32) | ((EntityID)version);
}

EntityIndex GetEntityIndex(EntityID id)
{
    return id >> 32;
}

EntityVersion GetEntityVersion(EntityID id)
{
    return (EntityVersion)id;
}

bool IsEntityValid(EntityID id)
{
    return (id >> 32) != EntityIndex(-1);
}
