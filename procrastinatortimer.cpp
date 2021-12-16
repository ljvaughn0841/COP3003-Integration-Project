#include "procrastinatortimer.h"
#include <QDebug>
//! defualt constructor
ProcrastinatorTimer::ProcrastinatorTimer() = default; // define trivial default constructor
/*!
 * \brief ProcrastinatorTimer::calcTimeEarned
 *
 * time earned increases on a curve starting off high
 * in order to quickly pay off the debt and gradually getting lower
 * until it reaches normal rate (1/ difficulty)
 * This insentivizes the user to continue for at least 2 minutes
 * in order to see the rewards of their time investment.
 */
void ProcrastinatorTimer::calcTimeEarned()
{
    static const double shiftLeft = 42;
    static const double curveSmoothness = 200;

    timeEarned += curveSmoothness / (timeRunning + shiftLeft) + 1. / difficulty;
    qDebug() << timeEarned;
}
