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

#ifndef SENSORS_H
#define SENSORS_H

#include <QWidget>
#include <QMessageBox>
#include "sensorgraph.h"

namespace Ui {
    class Sensors;
}

class Sensors : public QWidget
{
    Q_OBJECT

public:
    explicit Sensors(QWidget *parent = 0);
    ~Sensors();

    void updateTempsView(QString,QString);
    void updateHumidView(QString);

    QString checkTempCmd();
    QString checkHumidCmd();

public slots:

signals:
    void updateSensorBtnClicked();


private:
    Ui::Sensors *ui;

    SensorGraph *sg;

    QStringList addrList;     //list of unique addresses found in database
    void cacheAddr();


private slots:

    void showGraph();


};

#endif // SENSORS_H
