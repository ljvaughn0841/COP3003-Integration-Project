#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timermode.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Move the timer into timermode class and rename it to clock ?
    // ---------------------------------------------------------------------------------------------
    timer = new QTimer(this); // Creates a timer (consider renaming timer to clock)
    connect(timer, SIGNAL(timeout()), this, SLOT(myfunction()));
    // the sender (timer) sends a signal when timer times out to this (MainWindow class) to execute the function

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::on_shopButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_hourglassButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_settingsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_timerButton_clicked()
{
    timer->start(1000);             // starts the timer if the timer is already started it is restarted
    static TimerMode hourglass;     // static so that hourglass isnt destroyed and recreated every time button pressed
    hourglass.timerFlip();          // flips the direction the time flows in TimerMode (+/-)

}

// REMINDER you cannot purchase abilities if your negative or something
