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

#include "sensorgraph.h"
#include "ui_sensorgraph.h"



SensorGraph::SensorGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorGraph)
{
    ui->setupUi(this);

    this->setWindowTitle("Sensor Data");

    ui->qwtPlot->setAxisTitle(QwtPlot::yLeft, "Temperature");
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 40, 140);

    drawPlot();
}

SensorGraph::~SensorGraph()
{
    delete ui;
}

void SensorGraph::drawPlot() {


    QStringList list;
    QSqlQuery q;
    q.prepare("SELECT DISTINCT address FROM Temps");      //get each adress
    q.exec();
    while (q.next()) {
        QString address = q.value(0).toString();
        list.append(address);               //add each address to the list
        qDebug() << "address : " << q.value(0).toString();
        q.clear();
        q.prepare("SELECT temp, time FROM Temps WEHRE address = :address ORDER BY time DESC LIMIT 200");
        q.bindValue(":address",address);
        q.exec();
        while (q.next()) {
            //add temps to array
            //add timestamps to qwt plot label
        }
    }

    if(!list.isEmpty()){

    }
}
