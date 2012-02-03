/*
QHardwareKontrol is part of the openGreenHouse package of software sources

Written by: Travis McCann
Copywrite GPL 2010-2012

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <QtSql>
#include <QTimer>
#include <QTime>
#include <boost/thread.hpp>
#include "QAsyncSerial.h"
#include "sensors.h"
#include "timer.h"
#include "target.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QAsyncSerial serial;
    QSqlDatabase db;
    QTimer *timer;

    Sensors *sens;

    //TODO: make Timer and Target inheret from same base abstract class.. implement better polymorphism here
    Timer *relay01;
    Timer *relay02;
    Timer *relay03;
    Timer *relay04;
    Target *relay05;
    Target *relay06;



    void dbConnect();



private slots:
    void onLineReceived(QString data);
    void checkRelays();
    void checkSensors();

};


#endif // MAINWINDOW_H
