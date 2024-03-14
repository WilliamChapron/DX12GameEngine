#include "pch.h"
//
//#include "Time.h"

Time::Time()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
    lastTime = startTime;
    currentTime = startTime;
    isPaused = false;
}

void Time::UpdateTime()
{
    if (!isPaused) {
        lastTime = currentTime;

        QueryPerformanceCounter(&currentTime);

        deltaTime = static_cast<double>(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
    }
    else
    {
        SetDeltaTime(0.0f);
    }
}

void Time::SetDeltaTime(float newDeltaTime) {
    deltaTime = newDeltaTime;
}

double Time::GetElapsedTime() {
    return static_cast<double>(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
}

double Time::GetDeltaTime(){
    return deltaTime;
}

int Time::GetFramePerSecond()
{
    return static_cast<int>(floor(1.0f / GetDeltaTime()));
}

void Time::Pause() {
    isPaused = true;
}

void Time::Resume() {
    isPaused = false;
}