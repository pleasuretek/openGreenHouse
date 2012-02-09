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

#include "target.h"
#include "ui_target.h"

Target::Target(QWidget *parent) :
    Relay(parent),
    ui(new Ui::Target)
{
    ui->setupUi(this);
    relayID = 0; //init to invalid relayID
}

Target::Target(QWidget *parent, int id, int md) :
    Relay(parent),
    ui(new Ui::Target)
{
    ui->setupUi(this);
    relayID = id;
    mode = md;   //mode 0 = temps; 1 = humidity; 2 = c02

    cacheTarget();  //read values from database
    connect(ui->updateBtn, SIGNAL(clicked()), this, SIGNAL(update()));
    connect(ui->revertBtn, SIGNAL(clicked()), this, SLOT(cacheTarget()));
}

Target::~Target()
{
    delete ui;
}

void Target::setTitle(QString label) {
    ui->groupBox->setTitle(label);
}

void Target::setLabel(QString label) {
    ui->label->setText(label);
}

QString Target::check() {

    QString cmd = relayID.toString();
    QSqlQuery q;

    switch(mode.toInt()){
    case 0:    //temperature value
        float valb;
        q.prepare("SELECT temp FROM Temps ORDER BY time DESC LIMIT 3"); //select address instead..
        if(!q.exec()) {
            QMessageBox err;
            err.setText("Data Base Error");
            err.setInformativeText(q.lastError().text());
            err.exec();
        }
        int it;
        it = 0;
        while (q.next()) {

            if( it == 1) {
                val = q.value(0).toFloat();
            } else if (it == 2) {
                valb = q.value(0).toFloat();
            }
            it++;
        }
        //average the two sensors in the room
        val += valb;
        val = val/2.0;
        break;

    case 1:   //humidity target
        q.prepare("SELECT humid FROM Humid ORDER BY time DESC LIMIT 1");
        if(!q.exec()) {
            QMessageBox err;
            err.setText("Data Base Error");
            err.setInformativeText(q.lastError().text());
            err.exec();
        }
        while(q.next()) {
            val = q.value(0).toFloat();
        }
        break;
    case 2:   //C02 target
        break;
    }


    if( ((val + pval)/2.0) < target) {   //average this reading with the last
        cmd.append(":off.");
    } else {
        cmd.append(":on.");
    }

    pval = val;  //set previous value for next run
    //qDebug() << cmd;
    return cmd;
}

QString Target::check(QTime) {
    return "";
}

bool Target::confirmChange() {
    bool ret;
    QMessageBox msgBox;
    QString txt = "Relay " + relayID.toString();
    txt.append(" has been modified.");
    msgBox.setText(txt);
    msgBox.setInformativeText("Are you sure you want to change relay " + relayID.toString() + " ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if( msgBox.exec() == QMessageBox::Yes) {
        ret = true;
    } else {
        ret = false;
    }
    return ret;
}


void Target::on_updateBtn_clicked()
{
    if(confirmChange()) {
        QSqlQuery q;
        q.prepare("SELECT * FROM Target WHERE relayID = :relayID");
        q.bindValue(":relayID", relayID);
        if(!q.exec()) {
            QMessageBox err;
            err.setText("Data Base Error");
            err.setInformativeText(q.lastError().text());
            err.exec();
        }
        if(q.next()){ //relay with that ID exists, update
            q.clear();
            q.prepare("UPDATE Target SET target = :target WHERE relayID = :relayID");
            q.bindValue(":target",ui->spinBox->value());
            q.bindValue(":relayID", relayID);
            if(!q.exec()) {
                //query failed print error message here...
                QMessageBox err;
                err.setText("Data Base Error");
                err.setInformativeText(q.lastError().text());
                err.exec();
            }
        } else { //no relay with that ID Insert new one
            q.clear();
            q.prepare("INSERT INTO Target (target, relayID) VALUES(:target, :relayID)");
            q.bindValue(":target", ui->spinBox->value());
            q.bindValue(":relayID", relayID);
            if(!q.exec()) {
                //query failed insert error here...
                QMessageBox err;
                err.setText("Data Base Error");
                err.setInformativeText(q.lastError().text());
                err.exec();
            }
        }
        cacheTarget();
        emit update();
    }
}

void Target::cacheTarget() {
    QSqlQuery q;
    q.prepare("SELECT target FROM Target WHERE relayID = :relayID");
    q.bindValue(":relayID",relayID.toInt());
    if(!q.exec()) {
        QMessageBox err;
        err.setText("Data Base Error");
        err.setInformativeText(q.lastError().text());
        err.exec();
    }
    while(q.next()) {
        target = q.value(0).toFloat();  //cache target from database
        ui->spinBox->setValue(q.value(0).toInt());  //set ui to value in database too (reuse query)
    }
}
