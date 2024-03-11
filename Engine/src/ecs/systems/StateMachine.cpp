#include "pch.h"

#include "StateMachine.h"


StateMachine::StateMachine() : currentState(-1) {}

void StateMachine::SetState(const std::string& stateName, int stateValue) {
    stateMap[stateName] = stateValue;
}


void StateMachine::SetStateEvent(int stateValue, std::function<void()> eventFunction) {
    stateEventTable[stateValue][-1] = eventFunction; 
}

void StateMachine::ChangeState(const std::string& stateName) {
    auto it = stateMap.find(stateName);
    if (it != stateMap.end()) {
        currentState = it->second;
    }
    else {
        std::cout << "State not found." << std::endl;
    }
}

void StateMachine::Update() {
    if (stateEventTable.find(currentState) != stateEventTable.end() &&
        stateEventTable[currentState].find(-1) != stateEventTable[currentState].end()) {
        stateEventTable[currentState][-1]();
    }
    else {
        std::cout << "No event defined for current state." << std::endl;
    }
}

int StateMachine::GetCurrentState() const {
    return currentState;
}
