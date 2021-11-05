#ifndef TIMERMODE_H
#define TIMERMODE_H


class TimerMode
{
private:
    float timeEarned;      // total time earned
    int timeRunning;     // time in seconds since the hourglass was last clicked
    bool timerDirection; // 0 = negative and 1 = positive


public:
    TimerMode();
    virtual ~TimerMode();
    void timerFlip();
    bool getTimerDirection();
    int getTimeEarned();

    virtual void calcTimeEarned();
    int getTimeRunning() const;
    void setTimeRunning();
};

#endif // TIMERMODE_H
