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
    sg->hide();

    cacheAddr();
    connect(ui->graphBtn, SIGNAL(clicked()), this, SLOT(showGraph()));
    connect(ui->updateTempBtn, SIGNAL(clicked()), this, SIGNAL(updateSensorBtnClicked()));

}

Sensors::~Sensors()
{
    delete ui;
}

void Sensors::cacheAddr() {
    //find unique addresses in database
    addrList.clear();
    QSqlQuery q;
    q.prepare("SELECT DISTINCT address FROM Temps");
    if(!q.exec()) {
        QMessageBox err;
        err.setText("Data Base Error");
        err.setInformativeText(q.lastError().text());
        err.exec();
    }
    while (q.next()) {
        addrList.append(q.value(0).toString());
        // qDebug() << q.value(0).toString();
    }
}

void Sensors::updateTempsView(QString addr, QString temp) {
    if(!addrList.isEmpty()){
        if(addrList.contains(addr)) {
            for (int i = 0; i < addrList.count(); i++) {
                if(addrList.at(i) == addr) {
                    switch(i){
                    case 0:
                        ui->tempLabel01->setText(temp);
                        break;
                    case 1:
                        ui->tempLabel02->setText(temp);
                        break;
                    case 2:
                        ui->tempLabel03->setText(temp);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

void Sensors::updateHumidView(QString humid) {
    ui->humidLabel->setText(humid);
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

void Sensors::showGraph() {

        sg->show();

}
