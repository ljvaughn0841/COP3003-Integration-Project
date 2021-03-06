/*! @file mainwindow.h
 *  @brief Header file for the main window.
 *
 *  Contains declarations for the pushbuttons, pointer to qtimer,
 *  pointer to timermode, int mode, and objects of the derived
 *  classes of the interface timermode.
 *
 *  @author Lou Vaughn
 *  @bug No known bugs.
 */
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
//LO1a.
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

    static void easyButton_clicked();

    static void mediumButton_clicked();

    static void hardButton_clicked();

    static void insaneButton_clicked();

    void zoneButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *pTimer;          // pointer to the Qtimer class
    TimerMode *pHourglass;   // pointer to the TimerMode class named hourglass
    int mode;               // mode is used to decide where to static cast the hourglass

    NormalTimer normal;
    ProcrastinatorTimer prcr;
    ZoneTimer zone;

};
#endif // MAINWINDOW_H
