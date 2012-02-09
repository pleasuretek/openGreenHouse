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
#include "tincrement.h"
#include "tracker.h"


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
    QTimer *hiResTimer;  //for a few seconds timing.. attach only light lifting to fire every few seconds

    Sensors *sens;

    enum TimerMode { TIMER, INCREMENT, TARGET };

    Relay *relay01;
    Relay *relay02;
    Relay *relay03;
    Relay *relay04;
    Relay *relay05;
    Relay *relay06;

    Tracker *tracker;


    void dbConnect();



private slots:
    void buildIFace();
    void onLineReceived(QString data);
    void checkRelays();
    void checkSensors();
    void checkHiRes();

};


#endif // MAINWINDOW_H
