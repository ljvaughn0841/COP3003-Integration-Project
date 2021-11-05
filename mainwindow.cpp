#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this); // Creates a timer

    hourglass = new NormalTimer(); // default is normal mode

    // put in slot the function pointed to by class thing
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
    qDebug() << "hourglass function";

    hourglass->updateTimeRunning();
    // some sort of switch or something to select the right method
    static_cast<NormalTimer*>(hourglass)->calcTimeEarned();

    // make a virtual function that returns time earned to replace what is below

    hourglass->getTimeEarned(); // This needs to be output to be the time displayed

    static QString timeText; // this string represents the time to display
    timeText.setNum(hourglass->getTimeEarned()); // the string is set to = the time earned

    qDebug() << "Time Earned = " << timeText;
    // TODO: FORMAT THE TEXT TO BE -> hours : seconds : minutes
    qDebug() << "timer direction = " << hourglass->getTimerDirection();

    qDebug() << "Timer running = " << hourglass->getTimeRunning();

    ui->timeLabel->setText(timeText); // the string is outputed to replace text in the timeLabel

}

// REMINDER you cannot purchase abilities if your negative or something

void MainWindow::on_procrastinatorButton_clicked()
{

}

