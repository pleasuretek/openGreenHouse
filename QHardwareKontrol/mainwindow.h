#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTimer>
#include <QTime>
#include "QAsyncSerial.h"
#include "sensorgraph.h"


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
    SensorGraph *sg;
    QTime lastOn;
    QTime lastOff;

    float ptemp;  //previous temperature
    float phumid; //previous humidity


    void dbConnect();

    void updateTempsView();
    void updateHumidView();


private slots:
    void onLineReceived(QString data);
    void getSensorData();
    void checkTime();
    void checkTemp();
    void checkHumid();

    //void setBloomTimer();  //

    void showGraph();
};


#endif // MAINWINDOW_H
