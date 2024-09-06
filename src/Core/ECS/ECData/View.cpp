#include "View.hpp"



Iterator::Iterator(EntityManager* entities, EntityIndex index, ComponentMask mask, bool all)
    : entities(entities), index(index), mask(mask), all(all)
{
}


bool Iterator::operator==(const Iterator& other) const
{
    return index == other.index || index == entities->entities.size();
}


bool Iterator::operator!=(const Iterator& other) const
{
    return index != other.index && index != entities->entities.size();
}

Iterator& Iterator::operator++()
{
    do
    {
        index++;
    }
    while (index < entities->entities.size() && !ValidIndex());
    return *this;
}

bool Iterator::ValidIndex() const
{
    return
        // It's a valid entity ID
        IsEntityValid(entities->entities[index].id) &&
        // It has the correct component mask
        (all || mask == (mask & entities->entities[index].mask)
    );
}

