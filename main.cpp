/*! @file main.cpp
 *  @brief main creates the main window.
 *
 *  Creates an object a for QApplication and passes it an int argc and
 *  a pointer to an array of characters argv.
 *  Creates an object w for MainWindow and the function show displays the
 *  main window to the user.
 *
 *  @author Lou Vaughn
 *  @bug No known bugs.
 */
#include "mainwindow.h"

#include <QApplication>

auto main(int argc, char *argv[]) -> int
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
