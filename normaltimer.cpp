#include "normaltimer.h"

NormalTimer::NormalTimer()
{

}

void NormalTimer::calcTimeEarned()
{
    if(timerDirection){
        timeEarned += 1 / 10;
    }
    else{
        timeEarned += 1 / 10 * -1;
    }

}
