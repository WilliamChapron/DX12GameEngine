// main.cpp


#include "pch.h"

//#include "core/Window.h"
//#include "core/Engine.h"







int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    Engine::GetInstance().Init(hInstance, nShowCmd);
    return 0;
}


