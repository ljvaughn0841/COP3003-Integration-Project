#include "zonetimer.h"
#include <QDebug>
//! setter for the ammount bet
void ZoneTimer::setAmmountBet(int newAmmountBet)
{
    qDebug();
    ammountBet = newAmmountBet;
    qDebug() << "Ammount Bet: " <<ammountBet;

}
//! getter for the ammount bet
auto ZoneTimer::getAmmountBet() const -> int
{
    return ammountBet;
}
//! default constructor
ZoneTimer::ZoneTimer()
= default;

/*!
 * \brief ZoneTimer::calcTimeEarned
 *
 * Overrides TimerMode's pure virtual calcTimeEarned
 * if the conditions are met the user recieves double their
 * bet with half the difficulty reduction.
 * This is essentially difficulty tax evasion that incentivises
 * time comitments in order to reduce your difficulty by about a level.
 *
 * \param ran
 * \param bet
 */
void ZoneTimer::calcTimeEarned(int ran, int bet, bool (*conditionMet)(int, int))//LO7.
{

    if(conditionMet(ran, bet)){
        static const double x = 2.0;
        timeEarned += timeRunning * x / (difficulty / x);
    }
    else{
        timeEarned -= 1. / difficulty;
    }
}
