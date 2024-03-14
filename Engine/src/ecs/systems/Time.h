#pragma once

class Time {
private:
    LARGE_INTEGER startTime;
    LARGE_INTEGER frequency;

    LARGE_INTEGER currentTime;
    LARGE_INTEGER lastTime;
    bool isPaused;

    double deltaTime;
public:

    Time();

    void UpdateTime();

    double GetElapsedTime();
    double GetDeltaTime();
    int GetFramePerSecond();
    void Pause();
    void Resume();
    void SetDeltaTime(float newDeltaTime);


};