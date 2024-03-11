#include "pch.h"
//
//#include "Time.h"

Time::Time()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
    lastTime = startTime;
    currentTime = startTime;
}

void Time::UpdateTime()
{
    lastTime = currentTime;

    QueryPerformanceCounter(&currentTime);
}

float Time::GetElapsedTime() {
    double res = static_cast<double>(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
    return (float)res;
}

float Time::GetDeltaTime(){
    double deltaTime = static_cast<double>(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;

    return (float)deltaTime;
}

int Time::GetFramePerSecond()
{
    return static_cast<int>(floor(1.0f / GetDeltaTime()));
}


