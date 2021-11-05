#ifndef NORMALTIMER_H
#define NORMALTIMER_H

#include "timermode.h"

class NormalTimer : public TimerMode
{
public:
    NormalTimer();
    void calcTimeEarned();
};

#endif // NORMALTIMER_H
