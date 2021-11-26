#ifndef TIMERMODE_H
#define TIMERMODE_H


class TimerMode // super class for all the modes for the timer
{
protected:  // protected so that the subclasses can change them freely
            // but they are encapsulated from the rest of the program

    double timeEarned;      // total time earned
    int timeRunning;        // time in seconds since the hourglass was last flipped
    bool timerDirection;    // 0 = negative and 1 = positive
    int difficulty;         // difficulty is used in the calcTimeEarned

public:
    TimerMode();
    ~TimerMode();
    void timerFlip();           // inverses the timers direction
    bool getTimerDirection();
    float getTimeEarned();

    void calcTimeEarned(); // For some reason this being virtual breaks the static_casting
    int getTimeRunning() const;
    void updateTimeRunning();   // increments the time running
    void setTimeEarned(float newTimeEarned);    // used for deducting timeEarned when purchasing mode
    int getDifficulty() const;
    void setDifficulty(int newDifficulty);
    void resetTimeRunning();
};

#endif // TIMERMODE_H
