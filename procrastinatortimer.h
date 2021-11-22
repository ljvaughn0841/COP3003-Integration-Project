#ifndef PROCRASTINATORTIMER_H
#define PROCRASTINATORTIMER_H

#include "timermode.h"

class ProcrastinatorTimer : public TimerMode
{
public:
    ProcrastinatorTimer();
    void calcTimeEarned();
};

#endif // PROCRASTINATORTIMER_H
