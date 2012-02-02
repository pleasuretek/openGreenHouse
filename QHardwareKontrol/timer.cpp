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

#include "timer.h"
#include "ui_timer.h"

Timer::Timer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    relayID = 0;  //default contstructor init to null
}

Timer::Timer(QWidget *parent, int id) :
    QWidget(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    relayID = id;
    this->on_revertBtn_clicked();   //read values from database
}

Timer::~Timer()
{
    delete ui;
}


QString Timer::check() {
    QString cmd;  //serial command
    QTime now = QTime::currentTime();
    QSqlQuery q;
    QTime on;
    QTime off;
    q.prepare("SELECT onTime, offTime FROM Timer WHERE relayID = :relayID");
    q.bindValue(":relayID",relayID);
    q.exec();
    while(q.next()) {
        QString son = q.value(0).toString();
        QString soff = q.value(1).toString();
        on = QTime::fromString(son,"hh:mm");
        off = QTime::fromString(soff,"hh:mm");
    }

    if (off > on) {
        if((now > on) && (now < off)) {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":on.");
            return cmd;
        } else {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":off.");
            return cmd;
        }
    } else if ( off < on ) {
        if(((now > on) && (now > off)) || (now < off )) {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":on.");
            return cmd;
        } else {
            cmd.clear();
            cmd.append(relayID.toString());
            cmd.append(":off.");
            return cmd;
        }
    }
}

void Timer::setTimerLabel(QString label) {
    ui->timerLabel->setTitle(label);
}


bool Timer::confirmChange() {
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


void Timer::on_updateBtn_clicked()
{
    if(confirmChange()) {
        QSqlQuery q;
        q.prepare("SELECT * FROM Timer WHERE relayID = :relayID");
        q.bindValue(":relayID", relayID);
        q.exec();
        if(q.next()) { //relay with that ID exists... update
            q.clear();
            q.prepare("UPDATE Timer SET onTime = :onTime, offTime = :offTime WHERE relayID = 1");
            q.bindValue(":onTime",ui->onTmeSpinBox->time().toString("hh:mm"));
            q.bindValue(":offTime",ui->offTmeSpinBox->time().toString("hh:mm"));
            if(!q.exec()) {
                //Query failed, print error here ;)
            }
        } else {  //no relay ID so crete a new record
            q.clear();
            q.prepare("INSERT INTO Timer (onTime, offTime, relayID) VALUES(:onTime, :offTime, :relayID)");
            q.bindValue(":onTime",ui->onTmeSpinBox->time().toString("hh:mm"));
            q.bindValue(":offTime", ui->offTmeSpinBox->time().toString("hh:mm"));
            q.bindValue(":relayID",1);
            if(!q.exec()) {
                //Query failed, print yer freakin hER ROaR
            }
        }
        //TODO: Emit a signal to checkTime() in parent
    } else {  //confirm() returned false

    }
}

void Timer::on_revertBtn_clicked()
{
    QSqlQuery q;
    q.prepare("SELECT onTime, offTime FROM Timer WHERE relayID = :relayID");
    q.bindValue(":relayID", relayID);
    q.exec();
    while(q.next()) {
        QTime on = QTime::fromString(q.value(0).toString(), "hh:mm");
        ui->onTmeSpinBox->setTime(on);
        QTime off = QTime::fromString(q.value(1).toString(), "hh:mm");
        ui->offTmeSpinBox->setTime(off);
    }
}
