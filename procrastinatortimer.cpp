#include "procrastinatortimer.h"
#include <QDebug>

void ProcrastinatorTimer::calcTimeEarned()
{
    // timer starts with a big bonus and the bonus slowly goes down until it is eventually 1/difficulty
    timeEarned += 200. / (timeRunning + 42.) + 1. / difficulty;
    qDebug() << timeEarned;
}
