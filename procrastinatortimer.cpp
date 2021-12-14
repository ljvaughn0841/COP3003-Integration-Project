#include "procrastinatortimer.h"
#include <QDebug>

void ProcrastinatorTimer::calcTimeEarned()
{
    // timer starts with a big bonus in order to work off the payment
    // and the bonus slowly goes down until it is eventually reaches
    // 1/difficulty (the same as normal timers rate)
    static const double shiftLeft = 42;
    static const double curveSmoothness = 200;

    timeEarned += curveSmoothness / (timeRunning + shiftLeft) + 1. / difficulty;
    qDebug() << timeEarned;
}
