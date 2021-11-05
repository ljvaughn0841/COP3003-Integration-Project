#include "timermode.h"

TimerMode::TimerMode() // TimerModes constructor
{
    timeRunning = 0;
}

TimerMode::~TimerMode() // timer modes deconstructor
{

}


void TimerMode::timerFlip()
{
    timerDirection = !timerDirection;
}

bool TimerMode::getTimerDirection()
{
    return timerDirection;
}

int TimerMode::getTimeEarned()
{
    return timeEarned;
}

int TimerMode::getTimeRunning() const
{
    return timeRunning;
}

void TimerMode::setTimeRunning()
{
    timeRunning = ++timeRunning;
}
