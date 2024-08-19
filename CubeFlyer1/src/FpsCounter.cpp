#include "FpsCounter.h"

#include <chrono>
#include <iostream>

FpsCounter::FpsCounter()
    : framesCounter(0)
{
    timeSinceLastPrint = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch())
        .count();
}

void FpsCounter::incCounter() {
    long long time = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();

    long long duration = time - lastTime;
    lastTime = time;

    timeSinceLastPrint += duration;
    framesCounter++;
    if (timeSinceLastPrint > 1000) {
        std::cout << "current fps: " << framesCounter << std::endl;
        framesCounter = 0;
        timeSinceLastPrint %= 1000;
    }
}

