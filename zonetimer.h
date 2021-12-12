#ifndef ZONETIMER_H
#define ZONETIMER_H

#include "timermode.h"

class ZoneTimer : public TimerMode
{
private:
    int ammountBet{};

public:
    ZoneTimer();
    void calcTimeEarned(int ran, int bet, bool (*conditionMet)(int, int));
    void setAmmountBet(int newAmmountBet);
    int getAmmountBet() const;
};

#endif // ZONETIMER_H
