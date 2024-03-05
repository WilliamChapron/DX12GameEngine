#include "pch.h"

#include "StateMachine.h"
#include "State.h"

void StateMachine::AddState(State* state) {
    states.push_back(state);
}

void StateMachine::ChangeState(int index) {
    if (index >= 0 && index < states.size()) {
        if (currentState)
            currentState->exit(); // Sortir de l'�tat actuel
        currentState = states[index];
        currentState->enter(); // Entrer dans le nouvel �tat
    }
}

void StateMachine::UpdateCurrentState() {
    if (currentState)
        currentState->update();
}
