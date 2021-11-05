#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "timermode.h"
#include "normaltimer.h"

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
    void on_hourglassButton_clicked();

    void on_shopButton_clicked();

    void on_settingsButton_clicked();

    void on_timerButton_clicked();

    void hourglassFunction();

    void on_procrastinatorButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;          // pointer to a timer
    TimerMode *hourglass;
};
#endif // MAINWINDOW_H
