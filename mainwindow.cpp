#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this); // Creates a timer

    hourglass = new TimerMode();

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
    //static TimerMode hourglass;     // static so that hourglass isnt destroyed and recreated every time button pressed
    //hourglass.timerFlip();          // flips the direction the time flows in TimerMode (+/-)
}

void MainWindow::hourglassFunction(){   //triggers every second
    qDebug() << "hourglass function";
    hourglass->getTimeEarned();
}

// REMINDER you cannot purchase abilities if your negative or something
