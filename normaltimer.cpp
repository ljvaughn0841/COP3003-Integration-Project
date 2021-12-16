#include "normaltimer.h"
#include <QDebug>
//! default constructor
NormalTimer::NormalTimer() = default;

//! Normal calcTimeEarned
//! timeEarned increases by 1 / difficulty every seccond
void NormalTimer::calcTimeEarned()
{
    if(timerDirection){
        timeEarned += 1. / difficulty;
    }
    else{
        timeEarned += 1. / difficulty * -1;
    }
    qDebug() << timeEarned;
}
