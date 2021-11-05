#include "timermode.h"

#include <QtDebug>

TimerMode::TimerMode() // TimerModes constructor
{
    timeRunning = 1;
}

TimerMode::~TimerMode() // timer modes deconstructor
{

}


void TimerMode::timerFlip()
{
    qDebug() << "timer should flip";
    qDebug() << "pre flip " <<timerDirection;
    timerDirection = !timerDirection; // Why doesnt it work
    qDebug() << "post flip " <<timerDirection;
    qDebug() << "timer should have flipped";
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
