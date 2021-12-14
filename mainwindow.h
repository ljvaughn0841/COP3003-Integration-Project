#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <functional>
#include "timermode.h"
#include "normaltimer.h"
#include "procrastinatortimer.h"
#include "zonetimer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void hourglassButton_clicked();

    void shopButton_clicked();

    void settingsButton_clicked();

    void timerButton_clicked();

    void hourglassFunction();

    void procrastinatorButton_clicked();

    void easyButton_clicked();

    void mediumButton_clicked();

    void hardButton_clicked();

    void insaneButton_clicked();

    void zoneButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *pTimer;          // pointer to the Qtimer class
    TimerMode *pHourglass;   // pointer to the TimerMode class named hourglass
    int mode;               // mode is used to decide where to static cast the hourglass

};
#endif // MAINWINDOW_H
