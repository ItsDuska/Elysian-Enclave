#include "StateManager.h"
#include "State.h"


StateManager::StateManager()
    :dirty(false),
    newState(nullptr),
    isRemoving(false),
    isAdding(false),
    exitFlag(true)
{
}

StateManager::~StateManager()
{
    while (!states.empty())
    {
        states.pop();
    }
}

void StateManager::addState(std::unique_ptr<State> newState, bool isReplacing)
{
    dirty = true;
    isAdding = true;
    isRemoving = isReplacing;
    this->newState = std::move(newState);
}

void StateManager::removeState()
{
    dirty = true;
    isRemoving = true;
}

void StateManager::processChanges()
{
    if (!dirty)
    {
        return;
    }
    dirty = false;

    if (isRemoving && !states.empty())
    {
        states.pop();
        isRemoving = false;

        if (!states.empty() && !isAdding)
        {
            currentState()->wake();
            return;
        }
    }

    if (!isAdding)
    {
        return;
    }

    states.push(std::move(newState));
    isAdding = false;
}

State* StateManager::currentState()
{
    return states.top().get();
}

void StateManager::exitCall()
{
    exitFlag = false;
    dirty = true;
}

bool StateManager::isActive()
{
    return exitFlag;
}

