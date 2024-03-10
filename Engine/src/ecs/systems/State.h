#pragma once

class State
{
public:
    virtual void enter() = 0; // M�thode appel�e lors de l'entr�e dans l'�tat
    virtual void update() = 0; // M�thode appel�e lors de la mise � jour de l'�tat
    virtual void exit() = 0; // M�thode appel�e lors de la sortie de l'�tat
};