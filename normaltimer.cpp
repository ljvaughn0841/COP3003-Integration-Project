#include "normaltimer.h"

NormalTimer::NormalTimer()
{

}

void NormalTimer::calcTimeEarned()
{
    if(timerDirection){ // timerDirection = 1 for postive
        timeEarned = timeRunning / 10;
    }
    else{
        timeEarned = timeRunning / 10 * -1;
    }

}
