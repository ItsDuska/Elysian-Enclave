#pragma once
#include "Defines.hpp"
#include "EntityManager.hpp"


class Iterator
{
public:
    Iterator(EntityManager* entities, EntityIndex index, ComponentMask mask, bool all);

    inline EntityID operator*() const
    {
        return entities->entities[index].id;
    }


    bool operator==(const Iterator& other) const;

    bool operator!=(const Iterator& other) const;

    Iterator& operator++();

    bool ValidIndex() const;

private:
    EntityIndex index;
    EntityManager* entities;
    ComponentMask mask;
    bool all;
};



template<typename... ComponentTypes>
struct View
{
public:
    View(EntityManager& manager)
    {
        entityManagerPtr = &manager;
        if (sizeof...(ComponentTypes) == 0)
        {
            all = true;
            return;
        }

        all = false;
        // Unpack the template parameters into an initializer list
        int componentIds[] = { 0, util::generateNewID<ComponentTypes>() ... };
        for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
        {
            componentMask.set(componentIds[i]);
        }

    }
	
    const Iterator begin() const
    {
        int firstIndex = 0;
        
        while (firstIndex < entityManagerPtr->entities.size() &&
            (componentMask != (componentMask & entityManagerPtr->entities[firstIndex].mask)
                || !IsEntityValid(entityManagerPtr->entities[firstIndex].id)))
        {
            firstIndex++;
        }
        
        return Iterator(entityManagerPtr, firstIndex, componentMask, all);
    }

    const Iterator end() const
    {
         return Iterator(entityManagerPtr, EntityIndex(entityManagerPtr->entities.size()), componentMask, all);
    }

private:


private:
    EntityManager* entityManagerPtr;
    ComponentMask componentMask;
    bool all;
};

/*
TODO:
TÄÄ TOIMII MUTTA SE LOOPPI OTTAA KAIKKI EIKÄ VAIN NE PARIT KEILLÄ ON NE TIETYT.


*/