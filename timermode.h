#ifndef TIMERMODE_H
#define TIMERMODE_H


class TimerMode
{
protected:
    double timeEarned;      // total time earned
    int timeRunning;        // time in seconds since the hourglass was last flipped
    bool timerDirection;    // 0 = negative and 1 = positive
    int difficulty;         // difficulty is used in the calcTimeEarned

public:
    TimerMode();
    virtual ~TimerMode();
    void timerFlip();
    bool getTimerDirection();
    float getTimeEarned();

    void calcTimeEarned(); // For some reason removing virtual worked
    int getTimeRunning() const;
    void updateTimeRunning();
    void setTimeEarned(float newTimeEarned);
    int getDifficulty() const;
    void setDifficulty(int newDifficulty);
};

#endif // TIMERMODE_H
