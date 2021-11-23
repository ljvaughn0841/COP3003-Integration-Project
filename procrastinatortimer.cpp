#include "procrastinatortimer.h"
#include <QDebug>
ProcrastinatorTimer::ProcrastinatorTimer()
{

}

void ProcrastinatorTimer::calcTimeEarned()
{
    qDebug() << "procrastination timer";
    timeEarned += 1. / difficulty + 10/timeRunning;
}
