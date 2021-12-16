/*! @file procrastinatortimer.h
 *  @brief Header file for the procrastination timer mode.
 *
 *  Procrastinatior timer is a derived class of timer mode.
 *  Contains declarations for a default constructor
 *  and a function calcTimeEarned that overrides
 *  timermode's virtual calcTimeEarned
 *
 *  @author Lou Vaughn
 *  @bug No known bugs.
 */
#ifndef PROCRASTINATORTIMER_H
#define PROCRASTINATORTIMER_H

#include "timermode.h"

class ProcrastinatorTimer : public TimerMode
{
public:
    ProcrastinatorTimer();
    void calcTimeEarned();
};

#endif // PROCRASTINATORTIMER_H
