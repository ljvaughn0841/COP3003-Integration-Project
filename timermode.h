#ifndef TIMERMODE_H
#define TIMERMODE_H


class TimerMode
{
private:
    int time;           // total time earned
    int timeStarted;    // time since you started ? maybe remove this later we dont need to constantly monitor it?
    bool timerDirection; // 0 = negative and 1 = positive
public:
    TimerMode();
    void timerFlip();
    bool getTimerDirection();
};

#endif // TIMERMODE_H
