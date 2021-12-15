#include "zonetimer.h"
#include <QDebug>
void ZoneTimer::setAmmountBet(int newAmmountBet)
{
    qDebug();
    ammountBet = newAmmountBet;
    qDebug() << "Ammount Bet: " <<ammountBet;

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
        static const double x = 2.0;
        timeEarned += timeRunning * x / difficulty;
    }
    else{
        timeEarned -= 1. / difficulty;
    }
}
