#include "normaltimer.h"
#include <QDebug>
NormalTimer::NormalTimer()
{

}

void NormalTimer::calcTimeEarned()
{
    if(timerDirection){
        timeEarned += 1. / 10.;
    }
    else{
        timeEarned += 1. / 10. * -1;
    }
    qDebug() << timeEarned;
}
