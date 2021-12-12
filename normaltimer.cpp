#include "normaltimer.h"
#include <QDebug>
NormalTimer::NormalTimer() = default; // define trivial default constructor

void NormalTimer::calcTimeEarned() // consider breaking up the normalTimer into two and removing timeDirection
{
    if(timerDirection){
        timeEarned += 1. / difficulty;
    }
    else{
        timeEarned += 1. / difficulty * -1;
    }
    qDebug() << timeEarned;
}
