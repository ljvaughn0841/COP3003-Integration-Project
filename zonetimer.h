/*! @file zonetimer.h
 *  @brief Header file for the zone timer mode.
 *
 *  Zone timer is a derived class of timer mode.
 *  Contains declarations for a default constructor
 *  and a function calcTimeEarned that overrides
 *  timermode's virtual calcTimeEarned
 *
 *  @author Lou Vaughn
 *  @bug No known bugs.
 */
#ifndef ZONETIMER_H
#define ZONETIMER_H

#include "timermode.h"

class ZoneTimer : public TimerMode
{
private:
    int ammountBet = 0;

public:
    ZoneTimer();
    static void calcTimeEarned(int ran, int bet, bool (*conditionMet)(int, int));
    void setAmmountBet(int newAmmountBet);
    int getAmmountBet() const;
};

#endif // ZONETIMER_H
