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

#include "sensors.h"
#include "ui_sensors.h"

Sensors::Sensors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sensors)
{
    ui->setupUi(this);

    sg = new SensorGraph();
    showGraph(false);

    connect(ui->graphBtn, SIGNAL(clicked()), this, SLOT(showGraph()));
   // connect(ui->updateTempBtn, SIGNAL(clicked()), this, SLOT(checkTemp()));
}

Sensors::~Sensors()
{
    delete ui;
}

void Sensors::updateTempsView() {
    //find unique addresses in database first
    QStringList list;
    QSqlQuery q;
    q.prepare("SELECT DISTINCT address FROM Temps");
    q.exec();
    while (q.next()) {
        list.append(q.value(0).toString());    //list of unique addresses found in database
        // qDebug() << q.value(0).toString();
    }

    if(!list.isEmpty()){
        //now select most recent for each address
        int i =0;  //i is count for each individual address
        while (i<list.count()){
            q.clear();
            q.prepare("SELECT temp FROM Temps WHERE address = :address ORDER BY time DESC LIMIT 1");
            q.bindValue(":address", list.at(i));
            q.exec();
            while (q.next()){
                switch(i){  //TODO: rather than switch on i, find a way to relate unique addresses to gui elements (and be able to customize gui elements and rename labels by user)
                case 0:
                    ui->tempLabel01->setText(q.value(0).toString());
                    //qDebug() << q.value(0).toString();
                    break;
                case 1:
                    ui->tempLabel02->setText(q.value(0).toString());
                    //qDebug() << q.value(0).toString();
                    break;
                case 2:
                    ui->tempLabel03->setText(q.value(0).toString());
                    //qDebug() << q.value(0).toString();
                    break;
                }
            }
            i++;
        }
    }
}

void Sensors::updateHumidView() {
    QSqlQuery q;
    q.prepare("SELECT humid FROM Humid ORDER BY time DESC LIMIT 1");
    q.exec();
    while(q.next()){
        ui->humidLabel->setText(q.value(0).toString());
    }

}

QString Sensors::checkTempCmd() {
    QString cmd;
    cmd = "T:.";
    return cmd;
}

QString Sensors::checkHumidCmd() {
    QString cmd;
    cmd = "H:.";
    return cmd;
}

void Sensors::showGraph(bool show) {
    if(show) {
        sg->show();
    } else {
        sg->hide();
    }
}
