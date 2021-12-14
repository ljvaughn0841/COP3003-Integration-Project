#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pTimer = new QTimer(this); // Creates a timer which is a pointer to the Qtimer

    connect(pTimer, SIGNAL(timeout()), this, SLOT(hourglassFunction()));
    // the sender (timer) sends a signal when timer times out to execute the hourglass function in the slot

    pHourglass = new NormalTimer(); // Creates hourglass with the NormalTimer
    // Even though hourglass is declared as a pointer to TimerMode it can point to NormalTimer
    // because it is a subtype of TimerMode. Subtyping is closely related to object oriented inheritance.
    // For something to be a subtype it must be able to act as a substitute of the supertype
    // it can do this by containing the elements of the supertype.
    // inheritance in object oriented programming allows for codesharing and overriding between classes which
    // means a derived class is a subtype of the superclass because they contain shared elements.

    mode = 1; // since the hourglass's default is normal mode the mode is default 1

}

MainWindow::~MainWindow()
{
    delete ui;
    delete pTimer;
    delete pHourglass;
}

void MainWindow::on_shopButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // sets the page to the shop page
}

void MainWindow::on_hourglassButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // sets the page to the hourglass page
}

void MainWindow::on_settingsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2); // sets the page to the settings page
}

void MainWindow::on_timerButton_clicked()
{
    static const int sec = 1000; // 1000ms = 1s
    pTimer->start(sec); // starts the timer and if the timer is already started it is restarted
    // timer executes the connected hourglassFunction every second

    qDebug() << pHourglass->getTimerDirection();
    pHourglass->timerFlip();          // flips the direction the time flows in TimerMode (+/-)
    qDebug() << pHourglass->getTimerDirection();
}


// I couldn't come up with anything clever to demonstrate operations that take functions as arguments
// This function just checks to see if the some basic conditions
auto conditionMet(int x, int y) -> bool{
    return x >= y; // using zone as an example if timerRunning >= the ammount the user bet
}

void MainWindow::hourglassFunction(){   //triggers every second
    qDebug();
    qDebug() << "hourglass function";

    pHourglass->updateTimeRunning(); // increments time running
    // timer running is up here because it should never be zero in case it is used as the divisor in a formula

    if(!pHourglass->getTimerDirection() && pHourglass->getTimeRunning() == 1){
        qDebug() << "Switching back to normal mode direction negative & timerRunning = 1";
        mode = 1;
    }
    int ran = pHourglass->getTimeRunning();
    int bet = static_cast<ZoneTimer*>(pHourglass)->getAmmountBet();

    // dynamic disbatch selects the calcTimeEarned function depending on the selected mode
    switch (mode) {
    case 1:
        qDebug() << "Normal Timer";
        ui->modeLabel->setText("Normal Mode");
        static_cast<NormalTimer*>(pHourglass)->calcTimeEarned();
        break;
    case 2:
        qDebug() << "Procrastinator Timer";
        ui->modeLabel->setText("Procrastinator Mode");
        static_cast<ProcrastinatorTimer*>(pHourglass)->calcTimeEarned();
        static const int mins30 = 1800;
        if(conditionMet(ran, mins30)){    // checks if timer ran for more than 30 mins
            mode = 1;   // if the condition is met then after recieving your points the mode goes back to normal
            // timeRunning doesnt need to be reset here
        }
        break;
    case 3:
        qDebug() << "Zone Timer";
        ui->modeLabel->setText("Zone Mode");
        static_cast<ZoneTimer*>(pHourglass)->calcTimeEarned(ran, bet, &conditionMet); // passes integers ran and bet as well as the bool function conditionMet
        if(conditionMet(ran, bet)){
            mode = 1;   // if the condition is met then after recieving your points the mode goes back to normal
            // timeRunning doesnt need to be reset here
        }
        break;
    }



    // make a virtual function that returns time earned to replace what is below

    static QString timeText; // this string represents the time to display
    timeText.setNum(static_cast<int>(pHourglass->getTimeEarned())); // the string is set to = the time earned

    // TODO(me): format timeText to be -> hours : seconds : minutes

    ui->timeLabel->setText(timeText); // the string is outputed to replace text in the timeLabel

    // doesnt change anything in the window just helps with debugging
    qDebug() << "Time Earned = " << timeText;
    qDebug() << "timer direction = " << pHourglass->getTimerDirection();
    qDebug() << "Timer running = " << pHourglass->getTimeRunning();

}

// REMINDER you cannot purchase abilities if your negative

// hourglass->getTimeEarned() < 600 && hourglass->getTimerDirection() && hourglass->getTimeEarned() > 0
void MainWindow::on_procrastinatorButton_clicked()
{
    const int mins10 = 600;

    if(pHourglass->getTimeEarned() < mins10 && pHourglass->getTimeEarned() > 0){
        // turn on procrastination mode if time earned is less than 10 mins, greater than zero and the timer is
        // moving in the positive direction (this also means that it wont start the hourglass)
        if(!pHourglass->getTimerDirection()){ // if the timer is running in negative direction
            qDebug() << "Timer is negative";
            on_timerButton_clicked(); // flips the timers direction and restarts the timer such that the timerRunning resets
        }

        else{
            pHourglass->resetTimeRunning(); // sets timeRunning to 0
            // timer running resets here because if the timer was running and you activate procrastination mode
            // you probably werent actually doing your work while running the timer
        }

        const int timeDebt2Mins = 330;
        // using the integegral of the calcTimeEarned function for the ProcrastinatorTimer
        // a 330 seccond debt would be paid off after running procrastination mode for two minutes
        pHourglass->setTimeEarned(pHourglass->getTimeEarned()-timeDebt2Mins); // deducts 330 seconds from timeEarned


        mode = 2;// turns on procrastination mode

        ui->stackedWidget->setCurrentIndex(1); // brings the user back to the hourglass page
    }
    else{
        // Popup error explaining problem
    }


}

void MainWindow::on_zoneButton_clicked()
{
    static const int zoneMinBet = 1800; // 1800s = 30m
    if( mode != 3){
        QString ammountWagered = ui-> lineEdit->text();
        int bet = ammountWagered.toInt();

        if(pHourglass->getTimeEarned() > static_cast<double>(bet) && zoneMinBet < bet){
            // turn on zone mode if time earned greater than zero and the timer is

            // if not moving in the positive direction
            if(!pHourglass->getTimerDirection()){ // if the timer is running in negative direction
                qDebug() << "Timer is negative";
                on_timerButton_clicked(); // flips the timers direction and restarts the timer such that the timerRunning resets
            }

            else{// so the timerRunning is reset in the else below
                pHourglass->resetTimeRunning(); // sets timeRunning to 0

            }

            mode = 3;// turns on zone mode

            static_cast<ZoneTimer*>(pHourglass)->setAmmountBet(bet);
            ui->stackedWidget->setCurrentIndex(1); // brings the user back to the hourglass page
        }
        else{
            // Popup error explaining problem
        }
    }
}

enum difficulty{easy, medium = 2, hard = 4, insane = 8};

// the base rate for earned time is 1 / difficulty
void MainWindow::on_easyButton_clicked()
{
    pHourglass->setDifficulty(easy);    // sets difficulty to 1
}


void MainWindow::on_mediumButton_clicked()
{
    pHourglass->setDifficulty(medium);    // sets difficulty to 2
}


void MainWindow::on_hardButton_clicked()
{
    pHourglass->setDifficulty(hard);    // sets difficulty to 4
}


void MainWindow::on_insaneButton_clicked()
{
    pHourglass->setDifficulty(insane);    // sets difficulty to 8
}
