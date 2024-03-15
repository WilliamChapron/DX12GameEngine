#pragma once

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

    void Update();

    KeyState GetKeyState(char key) const;

    const std::unordered_map<char, KeyState>& GetKeyStates() const;

    POINT GetMousePosition() const;

    void ResetMousePosition();

private:

    WindowProperties* m_wndProps;

    void HandleKeyboardInput();

    void HandleMouseInput();

    KeyState GetKeyStateHelper(char key) const;

    std::unordered_map<char, KeyState> keyStates;
};