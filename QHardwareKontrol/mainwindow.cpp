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


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("QGrowRoomController");

    //TODO: make a chooser to allow user to select which port --probably in a prefs widget
    serial.open("/dev/ttyUSB0",9600);  //open serial port
    connect(&serial, SIGNAL(lineReceived(QString)), this, SLOT(onLineReceived(QString)));

    dbConnect();  //open database

    QWidget *main = new QWidget(this);
    QWidget *relayKeeper = new QWidget(this);

    sens = new Sensors(this);
    relay01 = new Timer(this,1);
    relay01->setTimerLabel("Bloom Light Timer");

    relay02 = new Timer(this,2);
    relay02->setTimerLabel("Osc Fan Timer 1");

    relay03 = new Target(this,3,0);   //relay 3, mode 0 (for target temp)
    relay03->setTitle("Target Temp");

    relay04 = new Target(this,4,1);   //relay 4, mode 1 (for target humid)
    relay04->setTitle("Target Humid");

    relay05 = new Timer(this,5);
    relay05->setTimerLabel("");

    relay06 = new Timer(this,6);
    relay06->setTimerLabel("");

    QVBoxLayout *relayLayout = new QVBoxLayout(this);
    relayLayout->addWidget(relay01);
    relayLayout->addWidget(relay02);
    relayLayout->addWidget(relay03);
    relayLayout->addWidget(relay04);
    relayLayout->addWidget(relay05);
    relayLayout->addWidget(relay06);

    relayKeeper->setLayout(relayLayout);

    QScrollArea *sa = new QScrollArea(this);
    sa->setWidget(relayKeeper);

    QVBoxLayout *vl = new QVBoxLayout(this);
    vl->addWidget(sens);
    vl->addWidget(sa);


    main->setLayout(vl);
    this->setCentralWidget(main);


    timer = new QTimer(this); //start relay timer
    connect(timer, SIGNAL(timeout()), this, SLOT(checkTime()));   //make checkTime fire on timer signal
    timer->start(30000);   //set to 300000  = 5minutes

    checkTime();  //set relays on startup

}

MainWindow::~MainWindow()
{
    delete sens;
    delete timer;
    serial.close();
    db.close();
    delete ui;
}

void MainWindow::dbConnect(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("SensorData");
    db.setUserName("root");
    db.setPassword("");  //Enter password for database user

    if(!db.open()) {
        qDebug() << "Database Error : ";
        qDebug() << db.lastError();
        qFatal("Failed to connect to database.");
    }

}

void MainWindow::onLineReceived(QString data) {
    //serial input detected... data is the line
    //temp data comes in the form of "T:address:temp;" example:  T:CE000DECAC4:77.7;
    QStringList list;

    list = data.split(":");
    if (!list.isEmpty()) {
        if(list.at(0) == "T"){ //the type is temperature
            QSqlQuery q;
            q.prepare("INSERT INTO Temps (address, temp) VALUES (:address, :temp)");
            q.bindValue(":address", list.at(1));
            q.bindValue(":temp", list.at(2));
            q.exec();
            sens->updateTempsView();
        }else if(list.at(0) == "H") { //the type is humidity
            QSqlQuery q;
            q.prepare("INSERT INTO Humid (humid) VALUES (:humid)");
            q.bindValue(":humid",list.at(1));
            q.exec();
            sens->updateHumidView();
        }
    }


}

void MainWindow::checkTime() { //this fires on timer signal
    //check relays
    serial.write(relay01->check());
    serial.write(relay02->check());
    serial.write(relay03->check());
    serial.write(relay04->check());
    serial.write(relay05->check());
    serial.write(relay06->check());

    // check sensors
    serial.write(sens->checkTempCmd());
    serial.write(sens->checkHumidCmd());

    sens->updateTempsView();
    sens->updateHumidView();
}

