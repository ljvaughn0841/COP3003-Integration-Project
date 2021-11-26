#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this); // Creates a timer which is a pointer to the Qtimer

    connect(timer, SIGNAL(timeout()), this, SLOT(hourglassFunction()));
    // the sender (timer) sends a signal when timer times out to execute the hourglass function in the slot

    hourglass = new NormalTimer(); // Creates hourglass with the NormalTimer
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
    delete timer;
    delete hourglass;
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
    timer->start(1000); // starts the timer and if the timer is already started it is restarted
    // timer executes the connected hourglassFunction every 1000ms = 1s

    qDebug() << hourglass->getTimerDirection();
    hourglass->timerFlip();          // flips the direction the time flows in TimerMode (+/-)
    qDebug() << hourglass->getTimerDirection();
}


// I couldn't come up with anything clever to demonstrate operations that take functions as arguments
// This function just checks to see if the some basic conditions
bool conditionMet(int x, int y){
    if(x >= y){ // using zone as an example if timerRunning >= the ammount the user bet
        return 1;

    }
    else{
        return 0;
    }
}

void MainWindow::hourglassFunction(){   //triggers every second
    qDebug();
    qDebug() << "hourglass function";

    hourglass->updateTimeRunning(); // increments time running
    // timer running is up here because it should never be zero in case it is used as the divisor in a formula

    if(!hourglass->getTimerDirection() && hourglass->getTimeRunning() == 1){
        qDebug() << "Switching back to normal mode direction negative & timerRunning = 1";
        mode = 1;
    }
    int ran = hourglass->getTimeRunning();
    int bet = static_cast<ZoneTimer*>(hourglass)->getAmmountBet();

    // dynamic disbatch selects the calcTimeEarned function depending on the selected mode
    switch (mode) {
    case 1:
        qDebug() << "Normal Timer Timer";
        static_cast<NormalTimer*>(hourglass)->calcTimeEarned();
        break;
    case 2:
        qDebug() << "Procrastinator Timer";

        static_cast<ProcrastinatorTimer*>(hourglass)->calcTimeEarned();
        if(conditionMet(ran, 1800)){    // checks if timer ran for more than 30 mins
            mode = 1;   // if the condition is met then after recieving your points the mode goes back to normal
            // timeRunning doesnt need to be reset here
        }
        break;
    case 3:
        qDebug() << "Zone Timer";

        static_cast<ZoneTimer*>(hourglass)->calcTimeEarned(ran, bet, &conditionMet); // passes integers ran and bet as well as the bool function conditionMet
        if(conditionMet(ran, bet)){
            mode = 1;   // if the condition is met then after recieving your points the mode goes back to normal
            // timeRunning doesnt need to be reset here
        }
        break;
    }



    // make a virtual function that returns time earned to replace what is below

    static QString timeText; // this string represents the time to display
    timeText.setNum((int)hourglass->getTimeEarned()); // the string is set to = the time earned

    // TODO: format timeText to be -> hours : seconds : minutes

    ui->timeLabel->setText(timeText); // the string is outputed to replace text in the timeLabel

    // doesnt change anything in the window just helps with debugging
    qDebug() << "Time Earned = " << timeText;
    qDebug() << "timer direction = " << hourglass->getTimerDirection();
    qDebug() << "Timer running = " << hourglass->getTimeRunning();

}

// REMINDER you cannot purchase abilities if your negative

// hourglass->getTimeEarned() < 600 && hourglass->getTimerDirection() && hourglass->getTimeEarned() > 0
void MainWindow::on_procrastinatorButton_clicked()
{

    if(hourglass->getTimeEarned() < 600 && hourglass->getTimeEarned() > 0){
        // turn on procrastination mode if time earned is less than 10 mins, greater than zero and the timer is
        // moving in the positive direction (this also means that it wont start the hourglass)
        if(!hourglass->getTimerDirection()){ // if the timer is running in negative direction
            qDebug() << "Timer is negative";
            on_timerButton_clicked(); // flips the timers direction and restarts the timer such that the timerRunning resets
        }

        else{
            hourglass->resetTimeRunning(); // sets timeRunning to 0
            // timer running resets here because if the timer was running and you activate procrastination mode
            // you probably werent actually doing your work while running the timer
        }

        hourglass->setTimeEarned(hourglass->getTimeEarned()-330); // deducts 330 seconds from timeEarned
        // using the integegral of the calcTimeEarned function for the ProcrastinatorTimer
        // the 330 seccond debt would be paid off after using procrastination mode for two minutes

        mode = 2;// turns on procrastination mode

        ui->stackedWidget->setCurrentIndex(1); // brings the user back to the hourglass page
    }
    else{
        // Popup error explaining problem
    }


}

void MainWindow::on_zoneButton_clicked()
{

    if( mode != 3){
        QString ammountWagered = ui-> lineEdit->text();
        int bet = ammountWagered.toInt();
        if(hourglass->getTimerDirection() && hourglass->getTimeEarned() > bet){
            // turn on zone mode if time earned greater than zero and the timer is

            // if not moving in the positive direction
            if(!hourglass->getTimerDirection()){ // if the timer is running in negative direction
                qDebug() << "Timer is negative";
                on_timerButton_clicked(); // flips the timers direction and restarts the timer such that the timerRunning resets
            }

            else{// so the timerRunning is reset in the else below
                hourglass->resetTimeRunning(); // sets timeRunning to 0

            }

            mode = 3;// turns on zone mode
            static_cast<ZoneTimer*>(hourglass)->setAmmountBet(bet);
            ui->stackedWidget->setCurrentIndex(1); // brings the user back to the hourglass page
        }
        else{
            // Popup error explaining problem
        }
    }
}



// the base rate for earned time is 1 / difficulty

void MainWindow::on_easyButton_clicked()
{
    hourglass->setDifficulty(1);    // sets difficulty to 1
}


void MainWindow::on_mediumButton_clicked()
{
    hourglass->setDifficulty(2);    // sets difficulty to 2
}


void MainWindow::on_hardButton_clicked()
{
    hourglass->setDifficulty(4);    // sets difficulty to 4
}


void MainWindow::on_insaneButton_clicked()
{
    hourglass->setDifficulty(8);    // sets difficulty to 8
}
