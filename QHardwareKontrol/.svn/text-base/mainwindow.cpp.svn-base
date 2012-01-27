/*
  //a small program to read and write serial to communicate with arduino project
  //author: Travis McCann
  //Copywrite Digital Growth Systems LLC.
*/




#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("QGrowRoomController");
    serial.open("/dev/ttyUSB0",9600);  //open serial port
    connect(&serial, SIGNAL(lineReceived(QString)), this, SLOT(onLineReceived(QString)));

    dbConnect();  //open database

    timer = new QTimer(this); //start relay timer
    connect(timer, SIGNAL(timeout()), this, SLOT(checkTime()));
    timer->start(10000);   //set to 300000  = 5minutes

    checkTime();  //set relays on startup


    sg = new SensorGraph();
    sg->hide();


    connect(ui->graphBtn, SIGNAL(clicked()), this, SLOT(showGraph()));
    connect(ui->updateTempBtn, SIGNAL(clicked()), this, SLOT(getSensorData()));

}

MainWindow::~MainWindow()
{
    serial.close();
    db.close();
    delete ui;
}

void MainWindow::dbConnect(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("SensorData");
    db.setUserName("root");
    db.setPassword("fuck.Y0u!23garden");

    if(!db.open()) {
        qDebug() << "Database Error : ";
        qDebug() << db.lastError();
        qFatal("Failed to connect to database.");
    }

}

void MainWindow::getSensorData() {
    QString cmd;
    cmd.append("T:.");  //command to get micro to check one wire bus for temps
    serial.write(cmd);
    cmd.clear();
    cmd.append("H:.");  //command to get micro to check DHT-22 humidity sensor
    serial.write(cmd);
}

void MainWindow::updateTempsView() {
    //find unique addresses in database first
    QStringList list;
    QSqlQuery q;
    q.prepare("SELECT DISTINCT address FROM Temps");
    q.exec();
    while (q.next()) {
        list.append(q.value(0).toString());
        // qDebug() << q.value(0).toString();
    }

    if(!list.isEmpty()){
        //now select most recent for each address
        int i =0;
        while (i<list.count()){
            q.clear();
            q.prepare("SELECT temp FROM Temps WHERE address = :address ORDER BY time DESC LIMIT 1");
            q.bindValue(":address", list.at(i));
            q.exec();
            while (q.next()){
                switch(i){
                case 0:
                    ui->tempLabel01->setText(q.value(0).toString());
                    qDebug() << q.value(0).toString();
                    break;
                case 1:
                    ui->tempLabel02->setText(q.value(0).toString());
                    qDebug() << q.value(0).toString();
                    break;
                case 2:
                    ui->tempLabel03->setText(q.value(0).toString());
                    qDebug() << q.value(0).toString();
                    break;
                }
            }
            i++;
        }
    }
}

void MainWindow::updateHumidView(){
    QSqlQuery q;
    q.prepare("SELECT humid FROM Humid ORDER BY time DESC LIMIT 1");
    q.exec();
    while(q.next()){
        ui->humidLabel->setText(q.value(0).toString());
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
            q.bindValue(":address:", list.at(1));
            q.bindValue(":temp", list.at(2));
            q.exec();
            updateTempsView();
        }else if(list.at(0) == "H") { //the type is humidity
            QSqlQuery q;
            q.prepare("INSERT INTO Humid (humid) VALUES (:humid)");
            q.bindValue(":humid",list.at(1));
            q.exec();
            updateHumidView();
        }
    }


}

void MainWindow::checkTime() { //this fires on timer signal

    //Serial format to send is "1:on." or "2:off."
    QString cmd;  //serial command string to be reused here
    QTime now = QTime::currentTime();
    QSqlQuery q;  // a query object to be reused


    //check time of relay 01 - main bloom light timer
    QVariant relayID = 1;

    QTime on = ui->timeRelay01On->time();
    QTime off = ui->timeRelay01Off->time();

    if (off > on) {
        if((now > on) && (now < off)) {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":on.");
            serial.write(cmd);
            qDebug() << cmd;
        } else {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":off.");
            serial.write(cmd);
            qDebug() << cmd;
        }
    } else if ( off < on ) {
        if(((now > on) && (now > off)) || (now < off )) {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":on.");
            serial.write(cmd);
            qDebug() << cmd;
        } else {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":off.");
            serial.write(cmd);
            qDebug() << cmd;
        }
    }
    relayID = 2;


    //now check relay 2 incremental
    relayID = 3;


    //now check relay 3 target temp
    cmd.clear();
    cmd.append(relayID.toString());
    float tempa = ui->tempLabel01->text().toFloat();
    tempa += ui->tempLabel02->text().toFloat();
    float temp = tempa/2.0;    //take average of the two sensors in the room
    float target = ui->targetTempBox->value();
    if (((temp + ptemp)/2.0) < target) {   //take average of this temp and last reading
        cmd.append(":off.");
        serial.write(cmd);
    } else {
        cmd.append(":on.");
        serial.write(cmd);
    }
    ptemp = temp;
    relayID = 4;


    //now check relay 4 target humid
    cmd.clear();
    cmd.append(relayID.toString());
    float humid = ui->humidLabel->text().toFloat();
    float hTarget = ui->targetHumidBox->value();
    if (((humid+phumid)/2) < hTarget) {
        cmd.append(":off.");
        serial.write(cmd);
    } else {
        cmd.append(":on.");
        serial.write(cmd);
    }
    phumid = humid;
    relayID = 5;


    //now check relay 5 veg timer 18 hour
    on = ui->timeRelay05On->time();
    off = ui->timeRelay05Off->time();

    if (off > on) {
        if((now > on) && (now < off)) {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":on.");
            serial.write(cmd);
            qDebug() << cmd;
        } else {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":off.");
            serial.write(cmd);
            qDebug() << cmd;
        }
    } else if ( off < on ) {
        if(((now > on) && (now > off)) || (now < off )) {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":on.");
            serial.write(cmd);
            qDebug() << cmd;
        } else {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":off.");
            serial.write(cmd);
            qDebug() << cmd;
        }
    }


    // check sensors
    getSensorData();
}


//void MainWindow::setRelay(int relayID) {


//    QString mode;
//    QSqlQuery q;
//    q.prepare("SELECT mode FROM Relay WHERE relayUID = :relayID");
//    q.bindValue(":relayID", relayID);
//    q.exec();
//    mode = q.value(0).toString();
//    switch (relayID) {
//    case 1:

//        break;
//    case 2:
//        break;
//    case 3:
//        break;
//    case 4:
//        break;
//    case 5:
//        break;
//    default:
//        //do nothing
//        break;
//    }

//    //insert into timer table
//    QSqlQuery q;
//    q.clear();
//    q.prepare("UPDATE Timer SET onTime = :onTime, offTime = :offTime, relayID = 1");
//    q.bindValue(":onTime",ui->timeRelay01On->time().toString("hh:mm"));
//    q.bindValue(":offTime",ui->timeRelay01Off->time().toString("hh:mm"));
//    q.exec();
//}

void MainWindow::checkTemp() {

}

void MainWindow::checkHumid() {

}

void MainWindow::showGraph() {
    sg->show();
}

