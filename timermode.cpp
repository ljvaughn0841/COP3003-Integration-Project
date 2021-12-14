#include "timermode.h"

#include <QtDebug>

auto TimerMode::getDifficulty() const -> int
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

    timerDirection = false; // starts negative because when the hourglassButton is clicked and timer is started the timer will flip directions
    difficulty = 2; // 2 is default difficulty
}

TimerMode::~TimerMode() = default; // timer modes default deconstructor


void TimerMode::timerFlip()
{
    qDebug() << "timer flip";
    timerDirection = !timerDirection;   // flips the timer direction
    timeRunning = 0;                    // sets time running back to zero

}

auto TimerMode::getTimerDirection() const -> bool
{
    return timerDirection;
}

auto TimerMode::getTimeEarned() const -> double
{
    return TimerMode::timeEarned;
}

void TimerMode::setTimeEarned(double newTimeEarned)
{
    timeEarned = newTimeEarned;
}

void TimerMode::calcTimeEarned(){} // virtual messed up the static_casting

auto TimerMode::getTimeRunning() const -> int
{
    return timeRunning;
}

void TimerMode::updateTimeRunning() // increments the time running by 1
{
    ++timeRunning;
}
