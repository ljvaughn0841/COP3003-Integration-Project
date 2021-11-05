#include "timermode.h"

#include <QtDebug>

TimerMode::TimerMode() // TimerModes constructor
{
    timeRunning = 1;
    timerDirection = 0;
}

TimerMode::~TimerMode() // timer modes deconstructor
{

}


void TimerMode::timerFlip()
{
    qDebug() << "timer flip";
    timerDirection = !timerDirection;   // flips the timer direction
    timeRunning = 0;                    // sets time running back to zero

}

bool TimerMode::getTimerDirection()
{
    return timerDirection;
}

float TimerMode::getTimeEarned()
{
    return TimerMode::timeEarned;
}

void TimerMode::setTimeEarned(float newTimeEarned)
{
    timeEarned = newTimeEarned;
}

void TimerMode::calcTimeEarned(){}

int TimerMode::getTimeRunning() const
{
    return timeRunning;
}

void TimerMode::updateTimeRunning()
{
    ++timeRunning;
}
