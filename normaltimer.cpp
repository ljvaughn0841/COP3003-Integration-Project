#include "normaltimer.h"
#include <QDebug>
NormalTimer::NormalTimer()
{

}

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
