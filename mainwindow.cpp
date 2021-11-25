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

void MainWindow::hourglassFunction(){   //triggers every second
    qDebug();
    qDebug() << "hourglass function";

    hourglass->updateTimeRunning(); // increments time running
    // timer running is up here because it should never be zero in case it is used as the divisor in a formula

    if(!hourglass->getTimerDirection() && hourglass->getTimeRunning() == 1){
        qDebug() << "Switching back to normal mode direction negative & timerRunning = 1";
        mode = 1;
    }

    // dynamic disbatch selects the calcTimeEarned function depending on the selected mode
    switch (mode) {
    case 1:
        qDebug() << "Normal Timer Timer";
        static_cast<NormalTimer*>(hourglass)->calcTimeEarned();
        break;
    case 2:
        qDebug() << "Procrastinator Timer";
        static_cast<ProcrastinatorTimer*>(hourglass)->calcTimeEarned();
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

void MainWindow::on_procrastinatorButton_clicked()
{

    if(hourglass->getTimeEarned() < 600 && hourglass->getTimerDirection() && hourglass->getTimeEarned() > 0){
        // turn on procrastination mode if time earned is less than 10 mins, greater than zero and the timer is
        // moving in the positive direction (this also means that it wont start the hourglass)
        if(!hourglass->getTimerDirection()){ // if the timer is running in negative direction
            qDebug() << "Timer is negative";
            on_timerButton_clicked(); // flips the timers direction and restarts the timer such that the timerRunning resets
        }

        hourglass->setTimeEarned(hourglass->getTimeEarned()-330); // deducts 330 seconds from timeEarned
        // using the integegral of the calcTimeEarned function for the ProcrastinatorTimer
        // the 330 seccond debt would be paid off after using procrastination mode for two minutes

        mode = 2;// turns on procrastination mode

        ui->stackedWidget->setCurrentIndex(1); // brings the user back to the hourglass page
    }
    else{
        // Popup error too high time earned
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

