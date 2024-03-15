#include "pch.h"

//
//#include "Input.h"
//
//#include "../../core/Window.h"
//
//#include "State.h"


Input::Input(WindowProperties _m_wndProps) : m_wndProps(&_m_wndProps){
    keyStates.clear();

    for (char key = 'A'; key <= 'Z'; ++key) {
        keyStates[key] = KeyState::Inactive;
    }
    keyStates[VK_SPACE] = KeyState::Inactive;
    keyStates[VK_SHIFT] = KeyState::Inactive;
    keyStates[VK_UP] = KeyState::Inactive;
    keyStates[VK_DOWN] = KeyState::Inactive;
    keyStates[VK_LEFT] = KeyState::Inactive;
    keyStates[VK_RIGHT] = KeyState::Inactive;
    keyStates[VK_LBUTTON] = KeyState::Inactive;
    keyStates[VK_RBUTTON] = KeyState::Inactive;
}

void Input::Update() {
    HandleKeyboardInput();
    HandleMouseInput();
    GetMousePosition();
}

void Input::HandleKeyboardInput() {
    for (char key = 'A'; key <= 'Z'; ++key) {
        keyStates[key] = GetKeyStateHelper(key);
    }
    keyStates[VK_SPACE] = GetKeyStateHelper(VK_SPACE);
    keyStates[VK_SHIFT] = GetKeyStateHelper(VK_SHIFT);
    keyStates[VK_UP] = GetKeyStateHelper(VK_UP);
    keyStates[VK_DOWN] = GetKeyStateHelper(VK_DOWN);
    keyStates[VK_LEFT] = GetKeyStateHelper(VK_LEFT);
    keyStates[VK_RIGHT] = GetKeyStateHelper(VK_RIGHT);
}

void Input::HandleMouseInput() {
    keyStates[VK_LBUTTON] = GetKeyStateHelper(VK_LBUTTON);
    keyStates[VK_RBUTTON] = GetKeyStateHelper(VK_RBUTTON);
}

KeyState Input::GetKeyStateHelper(char key) const {
    bool isKeyDown = GetAsyncKeyState(key) & 0x8000;
    auto search = keyStates.find(key);
    KeyState previousState = search->second;

    if (isKeyDown) {
        if (previousState == KeyState::Pressed || previousState == KeyState::Held) {
            return KeyState::Held;
        }
        else {
            return KeyState::Pressed;
        }
    }
    else {
        if (previousState == KeyState::Pressed || previousState == KeyState::Held) {
            return KeyState::Released;
        }
        else {
            return KeyState::Inactive;
        }
    }
}


KeyState Input::GetKeyState(char key) const {
    auto it = keyStates.find(key);
    if (it != keyStates.end()) {
        return it->second;
    }
    else {
        return KeyState::Inactive;
    }
}

const std::unordered_map<char, KeyState>& Input::GetKeyStates() const {
    return keyStates;
}

RECT GetWindowPosition(HWND hwnd) {
    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);
    return windowRect;
}

POINT Input::GetMousePosition() const {
    POINT cursorPos;
    GetCursorPos(&cursorPos); 
    ScreenToClient(m_wndProps->hwnd, &cursorPos);

    cursorPos.x -= (*m_wndProps).width / 2;
    cursorPos.y -= (*m_wndProps).height / 2;

    return cursorPos; 
}

void Input::ResetMousePosition() {
    POINT center;
    RECT windowRect = GetWindowPosition(m_wndProps->hwnd);
    
    ClientToScreen(m_wndProps->hwnd, &center); 
    
    center.x = (*m_wndProps).width / 2 + windowRect.left + 8;
    center.y = (*m_wndProps).height / 2 + windowRect.top + 31;

    SetCursorPos(center.x, center.y); 
}
