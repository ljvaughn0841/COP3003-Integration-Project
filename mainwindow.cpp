#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this); // Creates a timer

    hourglass = new NormalTimer(); // Creates hourglass with its default setting as normal mode

    mode = 1; // since the hourglass's default is normal mode the mode is default 1

    connect(timer, SIGNAL(timeout()), this, SLOT(hourglassFunction()));
    // the sender (timer) sends a signal when timer times out to execute the hourglass function in the slot

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
    timer->start(1000);             // starts the timer if the timer is already started it is restarted
    //static TimerMode hourglass;     // static so that hourglass isnt destroyed and recreated every time button pressed //delete this
    qDebug() << hourglass->getTimerDirection();
    hourglass->timerFlip();          // flips the direction the time flows in TimerMode (+/-)
    qDebug() << hourglass->getTimerDirection();
}

void MainWindow::hourglassFunction(){   //triggers every second
    qDebug();
    qDebug() << "hourglass function";

    hourglass->updateTimeRunning();
    // some sort of switch or something to select the right method


    switch (mode) {
    case 1:
        static_cast<NormalTimer*>(hourglass)->calcTimeEarned(); // TODO: for whatever reason the static casting isnt working
        qDebug() << "Normal Timer Timer";
        break;
    case 2:
        static_cast<ProcrastinatorTimer*>(hourglass)->calcTimeEarned();
        qDebug() << "Procrastinator Timer";
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

// REMINDER you cannot purchase abilities if your negative or something

void MainWindow::on_procrastinatorButton_clicked()
{
    if(!hourglass->getTimerDirection()){ // if the timer is running in negative direction
        qDebug() << "Timer is negative";
        on_timerButton_clicked(); // flips the timer for you
    }
    // turns on procrastination mode
    mode = 2;
}


void MainWindow::on_easyButton_clicked()
{
    hourglass->setDifficulty(1);
}


void MainWindow::on_mediumButton_clicked()
{
    hourglass->setDifficulty(2);
}


void MainWindow::on_hardButton_clicked()
{
    hourglass->setDifficulty(4);
}


void MainWindow::on_insaneButton_clicked()
{
    hourglass->setDifficulty(8);
}

