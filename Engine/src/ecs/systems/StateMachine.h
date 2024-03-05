#pragma once

class State;

class StateMachine
{
public:
    void AddState(State* state);

    void ChangeState(int index);

    void UpdateCurrentState();

private:
    std::vector<State*> states; // Liste des �tats
    State* currentState = nullptr; // �tat actuel
};

