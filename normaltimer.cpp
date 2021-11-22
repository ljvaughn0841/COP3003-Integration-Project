#include "normaltimer.h"
#include <QDebug>
NormalTimer::NormalTimer()
{

}

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
