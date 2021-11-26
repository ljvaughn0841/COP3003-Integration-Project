#include "timermode.h"

#include <QtDebug>

int TimerMode::getDifficulty() const
{
    return difficulty;
}

void TimerMode::setDifficulty(int newDifficulty)
{
    difficulty = newDifficulty;
}

void TimerMode::resetTimeRunning()
{
    timeRunning = 0;
}

TimerMode::TimerMode() // TimerModes constructor
{
    timeEarned = 0; // amount of total time earned from running the timer gained from calcTimeEanred function
    timeRunning = 0;    // the amount of time since the timeDirection was changed

    timerDirection = 0; // starts negative because when the hourglassButton is clicked and timer is started the timer will flip directions
    difficulty = 2; // 2 is default difficulty
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

void TimerMode::calcTimeEarned(){} // virtual messed up the static_casting

int TimerMode::getTimeRunning() const
{
    return timeRunning;
}

void TimerMode::updateTimeRunning() // increments the time running by 1
{
    ++timeRunning;
}
