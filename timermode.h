/*! @file timermode.h
 *  @brief Header file for the timer mode.
 *
 *  Timer mode is a superclass of all the other timers
 *  besides calcTimeEarned which is a virtual function
 *  that is called with a pointer to timermode all other functions
 *  are static and may be called with TimerMode::function();
 *  All the variables it contains are static so that they are shared
 *  amongst objects of its derived classes.
 *
 *  @author Lou Vaughn
 *  @bug No known bugs.
 */
#ifndef TIMERMODE_H
#define TIMERMODE_H

// LO1.
class TimerMode // super class for all the modes for the timer
{
protected:  // LO2a. protected so that the subclasses can change them freely
            // but they are encapsulated from the rest of the program

    inline static double timeEarned = 0;      // total time earned
    inline static int timeRunning = 0;        // time in seconds since the hourglass was last flipped
    inline static bool timerDirection = false;    // 0 = negative and 1 = positive
    inline static int difficulty = 2;         // difficulty is used in the calcTimeEarned


public:
    TimerMode();
    virtual ~TimerMode();
    static void timerFlip();           // inverses the timers direction
    static bool getTimerDirection() ;
    static double getTimeEarned() ;

    virtual void calcTimeEarned(); // LO6. pure virtual function makes TimerMode an interface
    static int getTimeRunning() ;
    static void updateTimeRunning();   // increments the time running
    static void setTimeEarned(double newTimeEarned);    // used for deducting timeEarned when purchasing mode
    static int getDifficulty() ;
    static void setDifficulty(int newDifficulty);
    static void resetTimeRunning();
};
#endif // TIMERMODE_H
