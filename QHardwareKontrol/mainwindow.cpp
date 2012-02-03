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

    this->setWindowTitle("Open GreenHouse Hardware Control");

    //TODO: make a chooser to allow user to select which port --probably in a prefs widget
    serial.open("/dev/ttyUSB0",115200);  //open serial port
    connect(&serial, SIGNAL(lineReceived(QString)), this, SLOT(onLineReceived(QString)));

    dbConnect();  //open database

    sens = new Sensors(this);
    connect(sens, SIGNAL(updateSensorBtnClicked()), this, SLOT(checkSensors()));

    relay01 = new Timer(this,1);   //lowpower relay
    relay01->setTitle("Bloom Light Timer");
    connect(relay01, SIGNAL(updateTimerSignal()), this, SLOT(checkRelays()));

    relay02 = new Timer(this,2);   //lowpower relay
    relay02->setTitle("Bloom Osc Fan Timer 1");
    connect(relay02, SIGNAL(updateTimerSignal()), this, SLOT(checkRelays()));

    relay03 = new Timer(this,3);   //lowpower relay
    relay03->setTitle("Veg Fan Timer");
    connect(relay03, SIGNAL(updateTimerSignal()), this, SLOT(checkRelays()));

    relay04 = new Target(this,4,0);   //high power relay
    relay04->setTitle("Bloom Target Temp");
    connect(relay04, SIGNAL(updateTargetSignal()), this, SLOT(checkRelays()));

    relay05 = new Target(this,5,1);    //high power relay
    relay05->setTitle("Target Humid");
    connect(relay05, SIGNAL(updateTargetSignal()), this, SLOT(checkRelays()));

    relay06 = new Timer(this,6);   //high power relay
    relay06->setTitle("Veg Light Timer");
    connect(relay06, SIGNAL(updateTimerSignal()), this, SLOT(checkRelays()));

    QWidget *main = new QWidget(this);
    QWidget *relayKeeper = new QWidget(this);

    QVBoxLayout *relayLayout = new QVBoxLayout();
    relayLayout->addWidget(relay01);
    relayLayout->addWidget(relay02);
    relayLayout->addWidget(relay03);
    relayLayout->addWidget(relay04);
    relayLayout->addWidget(relay05);
    relayLayout->addWidget(relay06);

    relayKeeper->setLayout(relayLayout);

    QScrollArea *sa = new QScrollArea(this);
    sa->setWidget(relayKeeper);

    QVBoxLayout *vl = new QVBoxLayout();
    vl->addWidget(sens);
    vl->addWidget(sa);


    main->setLayout(vl);
    this->setCentralWidget(main);


    timer = new QTimer(this); //start relay timer
    connect(timer, SIGNAL(timeout()), this, SLOT(checkRelays()));   //make checkRelays fire on timer signal
    connect(timer, SIGNAL(timeout()), this, SLOT(checkSensors()));  //make checkSensors fire on timer signal
    timer->start(20000);   //set to 300000  = 5minutes

    checkRelays();  //set relays on startup
    checkSensors();  //give the sensors a check too

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
    db.setPassword("fuck.Y0u!23garden");  //Enter password for database user

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


void MainWindow::checkRelays() {
    //check relays
    serial.write(relay01->check());
    //boost::this_thread::sleep( boost::posix_time::milliseconds(5) );
    serial.write(relay02->check());
    //boost::this_thread::sleep( boost::posix_time::milliseconds(5) );
    serial.write(relay03->check());
    //boost::this_thread::sleep( boost::posix_time::milliseconds(5) );
    serial.write(relay04->check());
    //boost::this_thread::sleep( boost::posix_time::milliseconds(5) );
    serial.write(relay05->check());
    //boost::this_thread::sleep( boost::posix_time::milliseconds(5) );
    serial.write(relay06->check());
    //boost::this_thread::sleep( boost::posix_time::milliseconds(5) );

}

void MainWindow::checkSensors() {

    // check sensors
    serial.write(sens->checkTempCmd());
    //boost::this_thread::sleep( boost::posix_time::milliseconds(5) );
    serial.write(sens->checkHumidCmd());
    //boost::this_thread::sleep( boost::posix_time::milliseconds(1) );

    sens->updateTempsView();
    sens->updateHumidView();
}

