#include "zonetimer.h"

void ZoneTimer::setAmmountBet(int newAmmountBet)
{
    ammountBet = newAmmountBet;
}

int ZoneTimer::getAmmountBet() const
{
    return ammountBet;
}

ZoneTimer::ZoneTimer()
{

}

void ZoneTimer::calcTimeEarned(int ran, int bet, bool (*conditionMet)(int, int))
{
    if(conditionMet(ran, bet)){
        timeEarned += timeRunning * 2. / difficulty;
    }
    else{
        timeEarned -= 1. / difficulty;
    }
}
