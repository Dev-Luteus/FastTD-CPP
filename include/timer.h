#ifndef TIMER_H
#define TIMER_H

#include "logger.h"
#include "raylib.h"

struct Timer
{
    Logger *log;
    char *name;
    double t0;
    double t1;
    double dt;

    Timer(Logger *log, char *name) : log{log}, name{name}
    {
        t0 = GetFrameTime();
        t1 = t0;
        dt = 0.0f;
    }

    ~Timer()
    {
        t1 = GetFrameTime();
        dt = t1 - t0;
        log->LogTimer(name, dt);
    }
};

#endif //TIMER_H
