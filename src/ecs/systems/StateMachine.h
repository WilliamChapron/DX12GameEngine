#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

class StateMachine {
public:
    StateMachine();

    void SetState(const std::string& stateName, int stateValue);
    void SetStateEvent(int stateValue, std::function<void()> eventFunction);

    void ChangeState(const std::string& stateName);
    void Update();

    int GetCurrentState() const;

private:
    using EventFunction = std::function<void()>;
    using StateEventMap = std::unordered_map<int, EventFunction>;

    int currentState;
    std::unordered_map<std::string, int> stateMap;
    std::unordered_map<int, StateEventMap> stateEventTable;
};