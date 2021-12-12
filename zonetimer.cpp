#include "zonetimer.h"

void ZoneTimer::setAmmountBet(int newAmmountBet)
{
    ammountBet = newAmmountBet;
}

auto ZoneTimer::getAmmountBet() const -> int
{
    return ammountBet;
}

ZoneTimer::ZoneTimer()
= default;

void ZoneTimer::calcTimeEarned(int ran, int bet, bool (*conditionMet)(int, int))
{
    if(conditionMet(ran, bet)){
        timeEarned += timeRunning * 2.0 / difficulty;
    }
    else{
        timeEarned -= 1. / difficulty;
    }
}
