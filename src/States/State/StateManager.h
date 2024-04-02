#pragma once
#include <stack>
#include <memory>

class State;

class StateManager
{
public:
    StateManager();
    ~StateManager();

    void addState(std::unique_ptr<State> newState, bool isReplacing = true);

    void removeState();

    void processChanges();
       
    State* currentState();

    void exitCall();

    bool isActive();

private:
    std::stack<std::unique_ptr<State>> states;
    std::unique_ptr<State> newState;
    bool dirty;
    bool isRemoving;
    bool isAdding;
    bool exitFlag;
};
