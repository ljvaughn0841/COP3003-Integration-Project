/*! @file mainwindow.cpp
 *  @brief the main window
 *
 *  Contains the setup for UI  and its connections as well as the
 *  logic for buttons, the timer, and its functions.
 *
 *  @author Lou Vaughn
 *  @bug No known bugs.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

//! Main Window's Constuctor.
    /*!
      Sets up the UI and connects the pushbuttons to their designated
      functions. Also connects the Qtimer to the hourglass function and initializes
      the pointer to Timermode and the mode.
    */
MainWindow::MainWindow(QWidget *parent) // LO1c.
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // connects buttons to the functions they are to execute
    connect(ui->shopButton,SIGNAL (released()), this, SLOT(shopButton_clicked()));
    connect(ui->hourglassButton,SIGNAL (released()), this, SLOT(hourglassButton_clicked()));
    connect(ui->settingsButton,SIGNAL (released()), this, SLOT(settingsButton_clicked()));
    connect(ui->timerButton,SIGNAL (released()), this, SLOT(timerButton_clicked()));
    connect(ui->procrastinatorButton,SIGNAL (released()), this, SLOT(procrastinatorButton_clicked()));
    connect(ui->zoneButton,SIGNAL (released()), this, SLOT(zoneButton_clicked()));
    connect(ui->easyButton,SIGNAL (released()), this, SLOT(easyButton_clicked()));
    connect(ui->mediumButton,SIGNAL (released()), this, SLOT(mediumButton_clicked()));
    connect(ui->hardButton,SIGNAL (released()), this, SLOT(hardButton_clicked()));
    connect(ui->insaneButton,SIGNAL (released()), this, SLOT(insaneButton_clicked()));



    pTimer = new QTimer(this); // Creates a pointer to the Qtimer named pTimer

    connect(pTimer, SIGNAL(timeout()), this, SLOT(hourglassFunction()));
    // the sender (timer) sends a signal when timer times out to execute the hourglass function in the slot

    pHourglass = new NormalTimer(); // Creates hourglass with the NormalTimer
    // LO5.
    // Even though hourglass is declared as a pointer to TimerMode it can point to NormalTimer
    // because it is a subtype of TimerMode. Subtyping is closely related to object oriented inheritance.
    // For something to be a subtype it must be able to act as a substitute of the supertype
    // it can do this by containing the elements of the supertype.
    // inheritance in object oriented programming allows for codesharing and overriding between classes which
    // means a derived class is a subtype of the superclass because they contain shared elements.

    mode = 1; // since the hourglass's default is normal mode the mode is default 1

}
//! A deconstructor.
    /*!
      deletes dynamically allocated resources
    */
MainWindow::~MainWindow()
{
    delete ui;
    delete pTimer;
    delete pHourglass;
}

//! When shopButton is clicked it goes to the shop page
void MainWindow::shopButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // sets the page to the shop page
}

//! When hourglassButton is clicked it goes to the hourglass page
void MainWindow::hourglassButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // sets the page to the hourglass page
}

//! When settingsButton is clicked it goes to the settings page
void MainWindow::settingsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2); // sets the page to the settings page
}


/*!
 * \brief MainWindow::timerButton_clicked
 *
 * sets the timer to start and execute the function every second
 * if the timer has already started this will restart it.
 * It also flips the timers direction in TimerMode.
 *
 */
void MainWindow::timerButton_clicked()
{
    static const int sec = 1000; // 1000ms = 1s
    pTimer->start(sec); // starts the timer and if the timer is already started it is restarted
    // timer executes the connected hourglassFunction every second

    qDebug() << TimerMode::getTimerDirection();
    TimerMode::timerFlip();          // flips the direction the time flows in TimerMode (+/-)
    qDebug() << TimerMode::getTimerDirection();
}


// I couldn't come up with anything clever to demonstrate operations that take functions as arguments
// This function just checks to see if the some basic conditions

/*!
 * \brief conditionMet
 *
 * I couldn't come up with anything clever to demonstrate
 * operations that take functions as arguments so this function
 * simply returns x>=y
 *
 * \param x
 * \param y
 * \return boolean
 */
auto conditionMet(int x, int y) -> bool{
    return x >= y; // using zone as an example if timerRunning >= the ammount the user bet
}
/*!
 * \brief MainWindow::hourglassFunction
 *
 * Executes every timeout signal from the Qtimer (in our case 1 seccond)
 * This function updates the values in TimerMode and the UI with the results.
 */
void MainWindow::hourglassFunction(){   //triggers every second
    qDebug();
    qDebug() << "hourglass function";

    TimerMode::updateTimeRunning(); // increments time running
    // timer running is up here because it should never be zero in case it is used as the divisor in a formula

    if(!TimerMode::getTimerDirection() && TimerMode::getTimeRunning() == 1){
        qDebug() << "Switching back to normal mode direction negative & timerRunning = 1";
        mode = 1;
        pHourglass = &normal;
    }

    if(TimerMode::getTimerDirection()){
        setStyleSheet("background-color:lightgreen");

    }
    else if(TimerMode::getTimeEarned() < 0) {
        setStyleSheet("background-color:#c33c3c");
    }
    else{
        setStyleSheet("background-color:lightcoral");
    }

    int ran = TimerMode::getTimeRunning() / TimerMode::getDifficulty();
    // LO3.
    // dynamic disbatch selects the calcTimeEarned function depending on the selected mode
    switch (mode) {
    case 1:
        qDebug() << "Normal Timer";
        ui->modeLabel->setText("Normal Mode");
        dynamic_cast<NormalTimer*>(pHourglass)->calcTimeEarned();
        break;
    case 2:
        qDebug() << "Procrastinator Timer";
        ui->modeLabel->setText("Procrastinator Mode");
        dynamic_cast<ProcrastinatorTimer*>(pHourglass)->calcTimeEarned();
        static const int mins30 = 1800;
        if(conditionMet(ran, mins30)){    // checks if timer ran for more than 30 mins
            mode = 1;   // if the condition is met then after recieving your points the mode goes back to normal
            pHourglass = &normal;
            // timeRunning doesnt need to be reset here
        }
        break;
    case 3:
        qDebug() << "Zone Timer";
        ui->modeLabel->setText("Zone Mode");
        int bet = dynamic_cast<ZoneTimer*>(pHourglass)->getAmmountBet();
        ZoneTimer::calcTimeEarned(ran, bet, &conditionMet); // passes integers ran and bet as well as the bool function conditionMet
        if(conditionMet(ran, bet)){
            mode = 1;   // if the condition is met then after recieving your points the mode goes back to normal
            pHourglass = &normal;
            // timeRunning doesnt need to be reset here
        }
        break;
    }

    // make a virtual function that returns time earned to replace what is below

    static QString timeText; // this string represents the time to display
    timeText.setNum(static_cast<int>(TimerMode::getTimeEarned())); // the string is set to = the time earned

    // TODO(me): format timeText to be -> hours : seconds : minutes

    ui->timeLabel->setText(timeText); // the string is outputed to replace text in the timeLabel

    // doesnt change anything in the window just helps with debugging
    qDebug() << "Time Earned = " << timeText;
    qDebug() << "timer direction = " << TimerMode::getTimerDirection();
    qDebug() << "Timer running = " << TimerMode::getTimeRunning();

}

/*!
 * \brief MainWindow::procrastinatorButton_clicked
 *
 * executes when the procrastinator button in the shop menu is clicked
 * if conditions are met to enter procrastination mode it updates the
 * pointer to hourglass, and the time earned taking away 330 secconds which
 * can be regained after two minutes in procrastinator mode.
 */
void MainWindow::procrastinatorButton_clicked()
{
    const int mins10 = 600;

    if(TimerMode::getTimeEarned() < mins10 && TimerMode::getTimeEarned() > 0 && mode !=2){
        // turn on procrastination mode if time earned is less than 10 mins, greater than zero and the timer is
        // moving in the positive direction (this also means that it wont start the hourglass)
        if(!TimerMode::getTimerDirection()){ // if the timer is running in negative direction
            qDebug() << "Timer is negative";
            timerButton_clicked(); // flips the timers direction and restarts the timer such that the timerRunning resets
        }

        else{
            TimerMode::resetTimeRunning(); // sets timeRunning to 0
            // timer running resets here because if the timer was running and you activate procrastination mode
            // you probably werent actually doing your work while running the timer
        }

        const int timeDebt2Mins = 330;
        // using the integegral of the calcTimeEarned function for the ProcrastinatorTimer
        // a 330 seccond debt would be paid off after running procrastination mode for two minutes
        TimerMode::setTimeEarned(TimerMode::getTimeEarned()-timeDebt2Mins); // deducts 330 seconds from timeEarned


        mode = 2;// turns on procrastination mode
        pHourglass = &prcr;

        ui->stackedWidget->setCurrentIndex(1); // brings the user back to the hourglass page
    }
    else{
        // Popup error explaining problem
    }


}
/*!
 * \brief MainWindow::zoneButton_clicked
 *
 * executes when zone button in the shop menu is clicked
 * if conditions are met to enter zone mode it updates the
 * pointer to hourglass, and the bet in zoneTimer
 */
void MainWindow::zoneButton_clicked()
{
    static const int zoneMinBet = 2; // 1800s = 30m
    if( mode != 3){
        QString ammountWagered = ui-> lineEdit->text();
        int bet = ammountWagered.toInt();
        if(TimerMode::getTimeEarned() > static_cast<double>(bet) && zoneMinBet < bet){
            // turn on zone mode if time earned greater than zero and the timer is

            // if not moving in the positive direction
            if(!TimerMode::getTimerDirection()){ // if the timer is running in negative direction
                qDebug() << "Timer is negative";
                timerButton_clicked(); // flips the timers direction and restarts the timer such that the timerRunning resets
            }

            else{// so the timerRunning is reset in the else below
                TimerMode::resetTimeRunning(); // sets timeRunning to 0

            }

            mode = 3;// turns on zone mode
            pHourglass = &zone;

            dynamic_cast<ZoneTimer*>(pHourglass)->setAmmountBet(bet);// need pHourglass to point respective timer when dynamic casting

            ui->stackedWidget->setCurrentIndex(1); // brings the user back to the hourglass page
        }
        else{
            // Popup error explaining problem
        }
    }
}


//! An enum where each difficulty is 2x the previous
enum difficulty{easy, medium = 2, hard = 4, insane = 8};

// the base rate for earned time is 1 / difficulty

//! Executes when easy button in settings is clicked
//! sets the difficulty to 1
void MainWindow::easyButton_clicked()
{
    TimerMode::setDifficulty(easy);    // sets difficulty to 1
}

//! Executes when :medium button in settings is clicked
//! sets the difficulty to 2
void MainWindow::mediumButton_clicked()
{
    TimerMode::setDifficulty(medium);    // sets difficulty to 2
}

//! Executes when hard button in settings is clicked
//! sets the difficulty to 4
void MainWindow::hardButton_clicked()
{
    TimerMode::setDifficulty(hard);    // sets difficulty to 4
}

//! Executes when insane button in settings is clicked
//! sets the difficulty to 8
void MainWindow::insaneButton_clicked()
{
    TimerMode::setDifficulty(insane);    // sets difficulty to 8
}
