#ifndef TIMERMODE_H
#define TIMERMODE_H


class TimerMode
{
protected:
    float timeEarned;      // total time earned
    int timeRunning;     // time in seconds since the hourglass was last clicked
    bool timerDirection; // 0 = negative and 1 = positive

public:
    TimerMode();
    virtual ~TimerMode();
    void timerFlip();
    bool getTimerDirection();
    float getTimeEarned();

    virtual void calcTimeEarned();
    int getTimeRunning() const;
    void updateTimeRunning();
    void setTimeEarned(float newTimeEarned);
};

#endif // TIMERMODE_H
