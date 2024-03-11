#pragma once

class Time {
private:
    LARGE_INTEGER startTime;
    LARGE_INTEGER frequency;

    LARGE_INTEGER currentTime;
    LARGE_INTEGER lastTime;
public:

    Time();

    void UpdateTime();

    float GetElapsedTime();
    float GetDeltaTime();
    int GetFramePerSecond();


};