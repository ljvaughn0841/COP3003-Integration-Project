#include "timermode.h"

TimerMode::TimerMode() // TimerModes constructor
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
