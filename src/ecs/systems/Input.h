﻿#pragma once

struct WindowProperties;

enum class KeyState {
    Pressed,
    Held,
    Released,
    Inactive
};

class Input {
public:
    Input(WindowProperties m_wndProps);

    // Met � jour l'�tat des entr�es 
    void Update();

    // Trouve l'�tat d'une touche en fonction de sa cl�
    KeyState GetKeyState(char key) const;

    // Trouve l'�tat de toutes les touches
    const std::unordered_map<char, KeyState>& GetKeyStates() const;

    // Trouve la position de la souris
    POINT GetMousePosition() const;

    void ResetMousePosition();

private:

    WindowProperties* m_wndProps;

    // M�thode pour g�rer les entr�es clavier
    void HandleKeyboardInput();

    // M�thode pour g�rer les clics de souris
    void HandleMouseInput();

    // V�rifie l'�tat de la touche sp�cifi�e par sa cl�
    KeyState GetKeyStateHelper(char key) const;

    // Stocke l'�tat des touches clavier
    std::unordered_map<char, KeyState> keyStates;
};