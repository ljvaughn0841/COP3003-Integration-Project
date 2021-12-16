/*! @file normaltimer.h
 *  @brief Header file for the normal timer mode.
 *
 *  Normal timer is a derived class of timer mode.
 *  Contains declarations for a default constructor
 *  and a function calcTimeEarned that overrides
 *  timermode's virtual calcTimeEarned.
 *
 *  @author Lou Vaughn
 *  @bug No known bugs.
 */
#ifndef NORMALTIMER_H
#define NORMALTIMER_H

#include "timermode.h"

class NormalTimer : public TimerMode
{
public:
    NormalTimer();
    void calcTimeEarned();
};

#endif // NORMALTIMER_H
